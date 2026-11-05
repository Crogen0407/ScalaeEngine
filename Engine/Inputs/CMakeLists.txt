add_library(Inputs INTERFACE)
add_library(Scalae::Inputs ALIAS Inputs)
target_include_directories(Inputs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Public)