cmake_minimum_required(VERSION 3.20)
project(ScalaeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ScalaeEngine INTERFACE)
add_library(Scalae::Engine ALIAS ScalaeEngine)

target_precompile_headers(ScalaeEngine 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include/pch.h
)

file(GLOB_RECURSE SCALAE_RUNTIME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE ALL_PUBLIC_DIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Runtime/Public"
)

file(GLOB_RECURSE ALL_PUBLIC_DIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Public"
)

set(MODULE_PUBLIC_DIRS "")
foreach(dir IN LISTS ALL_PUBLIC_DIRS)
    if(IS_DIRECTORY "${dir}"
       AND dir MATCHES "/Public$"
       AND NOT dir MATCHES "/(build|out|\\.vs)/")
        list(APPEND MODULE_PUBLIC_DIRS "${dir}")
    endif()
endforeach()

message(STATUS "Public dirs: ${MODULE_PUBLIC_DIRS}")
target_include_directories(ScalaeEngine INTERFACE ${MODULE_PUBLIC_DIRS})

list(FILTER SCALAE_RUNTIME_SOURCES EXCLUDE REGEX "/(build|out|\\.vs|CMakeFiles)/")

set_source_files_properties(${SHADER_FILES} PROPERTIES
    VS_SHADER_MODEL 5.0
)

add_executable(ScalaeRuntime ${SCALAE_RUNTIME_SOURCES})

target_compile_definitions(ScalaeRuntime PRIVATE UNICODE _UNICODE)
target_link_options(ScalaeRuntime PRIVATE -municode)
target_link_libraries(ScalaeRuntime PRIVATE Scalae::Engine Games)