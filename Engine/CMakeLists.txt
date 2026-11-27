cmake_minimum_required(VERSION 3.20)
project(ScalaeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# DirectXTex (기존과 동일)
add_library(DirectXTex STATIC IMPORTED GLOBAL)
set_target_properties(DirectXTex PROPERTIES
    IMPORTED_CONFIGURATIONS "Debug;Release"
    IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Library/DirectXTex/DirectXTex_debug.lib"
    IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Library/DirectXTex/DirectXTex.lib"
    MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
    MAP_IMPORTED_CONFIG_MINSIZEREL Release
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Include"
)
target_link_libraries(DirectXTex INTERFACE d3d11 dxgi ole32 windowscodecs uuid)

# 소스 수집
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
list(FILTER ENGINE_SOURCES EXCLUDE REGEX "/(build|out|\\.vs|CMakeFiles)/")
list(FILTER ENGINE_HEADERS EXCLUDE REGEX "/(build|out|\\.vs|CMakeFiles)/")

# 진입점(wWinMain이 있는 파일)은 라이브러리에서 분리
set(SCALAE_ENTRY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Runtime/Private/Main.cpp") # 실제 경로로 수정
list(REMOVE_ITEM ENGINE_SOURCES "${SCALAE_ENTRY_SOURCE}")
set(SCALAE_ENTRY_SOURCE "${SCALAE_ENTRY_SOURCE}" CACHE INTERNAL "")

# Public 폴더들
file(GLOB_RECURSE ALL_PUBLIC_DIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Public")
set(MODULE_PUBLIC_DIRS "")
foreach(dir IN LISTS ALL_PUBLIC_DIRS)
    if(IS_DIRECTORY "${dir}" AND dir MATCHES "/Public$"
       AND NOT dir MATCHES "/(build|out|\\.vs)/")
        list(APPEND MODULE_PUBLIC_DIRS "${dir}")
    endif()
endforeach()

add_library(ScalaeEngine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
add_library(Scalae::Engine ALIAS ScalaeEngine)

target_include_directories(ScalaeEngine PUBLIC ${MODULE_PUBLIC_DIRS})
target_precompile_headers(ScalaeEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/pch.h)
target_compile_definitions(ScalaeEngine PUBLIC UNICODE _UNICODE)
target_link_libraries(ScalaeEngine PUBLIC DirectXTex)