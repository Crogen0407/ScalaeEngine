add_library(Physics INTERFACE)
add_library(Scalae::Physics ALIAS Physics)
target_include_directories(Physics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Public)