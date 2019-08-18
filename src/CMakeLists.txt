set(EXE_NAME teslarc)

add_compile_options(
    "-Wall"
)

# Project source files
set(
    TESLARC_SRC ./main.cpp
)

add_executable(${EXE_NAME} ${TESLARC_SRC})
target_compile_features(${EXE_NAME} PUBLIC cxx_std_11)

target_link_libraries(${EXE_NAME} third_party)

# Add required include paths
target_include_directories(${EXE_NAME}
    PRIVATE ${EXTERN_RAPIDJSON_INCLUDE_DIR}
            ${EXTERN_CURL_INCLUDE_DIR}
)
