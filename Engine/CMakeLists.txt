cmake_minimum_required(VERSION 3.20)
project(ScalaeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ScalaeEngine INTERFACE)
add_library(Scalae::Engine ALIAS ScalaeEngine)

# DirectX
#-----------------------------------
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
target_link_libraries(ScalaeEngine INTERFACE DirectXTex)
#-----------------------------------


target_precompile_headers(ScalaeEngine 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include/pch.h
)

file(GLOB_RECURSE SCALAE_RUNTIME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE SCALAE_RUNTIME_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
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
list(FILTER SCALAE_RUNTIME_HEADERS EXCLUDE REGEX "/(build|out|\\.vs|CMakeFiles)/")

set_source_files_properties(${SHADER_FILES} PROPERTIES
    VS_SHADER_MODEL 5.0
)

add_executable(ScalaeRuntime ${SCALAE_RUNTIME_SOURCES} ${SCALAE_RUNTIME_HEADERS})

target_compile_definitions(ScalaeRuntime PRIVATE UNICODE _UNICODE)
target_link_options(ScalaeRuntime PRIVATE -municode)
target_link_libraries(ScalaeRuntime PRIVATE Scalae::Engine Games)