cmake_minimum_required(VERSION 3.20)
project(ScalaeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SCALAE_RUNTIME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(ScalaeEngine INTERFACE)
add_library(Scalae::Engine ALIAS ScalaeEngine)

target_include_directories(ScalaeEngine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(ScalaeEngine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h
)

list(FILTER SCALAE_RUNTIME_SOURCES EXCLUDE REGEX "/(build|out|\\.vs|CMakeFiles)/")

add_executable(ScalaeRuntime ${SCALAE_RUNTIME_SOURCES})
target_compile_definitions(ScalaeRuntime PRIVATE UNICODE _UNICODE)
target_link_options(ScalaeRuntime PRIVATE -municode)
target_link_libraries(ScalaeRuntime PRIVATE Scalae::Engine Game)