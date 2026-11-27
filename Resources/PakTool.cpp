#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct Entry { std::string path; uint64_t offset; uint64_t size; };

template <class T>
void Write(std::ofstream& o, T v) { o.write(reinterpret_cast<const char*>(&v), sizeof(T)); }

int main(int argc, char** argv)
{
    if (argc < 3) { std::cerr << "usage: PakTool <resource_dir> <out.pak>\n"; return 1; }
    fs::path root = argv[1], outPath = argv[2];

    std::vector<fs::path> files;
    for (auto& e : fs::recursive_directory_iterator(root))
        if (e.is_regular_file()) files.push_back(e.path());
    std::sort(files.begin(), files.end());          // 매번 같은 결과가 나오도록 정렬

    std::ofstream out(outPath, std::ios::binary | std::ios::trunc);
    out.write("SPAK", 4);
    Write<uint32_t>(out, 1);        // version
    Write<uint32_t>(out, 0);        // count (나중에 채움)
    Write<uint64_t>(out, 0);        // tocOffset (나중에 채움)

    std::vector<Entry> toc;
    for (auto& f : files)
    {
        std::ifstream in(f, std::ios::binary);
        std::vector<char> buf((std::istreambuf_iterator<char>(in)), {});

        std::string rel = fs::relative(f, root).generic_string();   // '/' 구분
        std::transform(rel.begin(), rel.end(), rel.begin(),
            [](unsigned char c) { return (char)std::tolower(c); });

        toc.push_back({ rel, (uint64_t)out.tellp(), (uint64_t)buf.size() });
        out.write(buf.data(), (std::streamsize)buf.size());
    }

    uint64_t tocOffset = (uint64_t)out.tellp();
    for (auto& e : toc)
    {
        Write<uint16_t>(out, (uint16_t)e.path.size());
        out.write(e.path.data(), (std::streamsize)e.path.size());
        Write<uint64_t>(out, e.offset);
        Write<uint64_t>(out, e.size);
    }

    out.seekp(8);                                   // magic(4) + version(4) 다음
    Write<uint32_t>(out, (uint32_t)toc.size());
    Write<uint64_t>(out, tocOffset);

    std::cout << "packed " << toc.size() << " files -> " << outPath << "\n";
    return 0;
}