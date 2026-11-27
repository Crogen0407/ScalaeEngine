add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources" "$<TARGET_FILE_DIR:Game>/Resources")

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Shaders/*.hlsl")

set_source_files_properties(${SHADER_FILES} PROPERTIES
    VS_SHADER_TYPE Vertex          # 파일마다 다르게 지정해야 함 (아래 참고)
    VS_SHADER_MODEL 5.0
    VS_SHADER_ENTRYPOINT main
    VS_SHADER_VARIABLE_NAME g_VS_Basic
    VS_SHADER_OUTPUT_HEADER_FILE "${CMAKE_BINARY_DIR}/Shaders/%(Filename).h"
)
target_sources(ScalaeEngine PRIVATE ${SHADER_FILES})

add_executable(Resources PakTool.cpp)
target_compile_features(Resources PRIVATE cxx_std_20)