set(EXE_NAME teslarc)

add_compile_options(
    "-Wall"
)

# Project source files
set(
    TESLARC_SRC ./main.cpp
                ./session.cpp
                ./charge.cpp
                ./util/user_prompt.cpp
                ./util/oauth.cpp
)

add_executable(${EXE_NAME} ${TESLARC_SRC})
target_compile_features(${EXE_NAME} PUBLIC cxx_std_11)
target_link_libraries(${EXE_NAME} third_party)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${EXE_NAME} PUBLIC TESLARC_DEBUG_ENABLED)
endif()
