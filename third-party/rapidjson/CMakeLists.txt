set(EXTERN_RAPIDJSON_VERSION 1.1.0)
set(
    EXTERN_RAPIDJSON_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/rapidjson-${EXTERN_RAPIDJSON_VERSION}/include"
    CACHE STRING "rapidjson include directory"
    FORCE
)

add_custom_command(
    OUTPUT ${EXTERN_RAPIDJSON_INCLUDE_DIR}
    COMMAND tar --skip-old-files -xzf "${CMAKE_CURRENT_SOURCE_DIR}/rapidjson-${EXTERN_RAPIDJSON_VERSION}.tar.gz" 
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rapidjson-${EXTERN_RAPIDJSON_VERSION}.tar.gz"
    COMMENT "Unpacking rapidjson"
    VERBATIM
)

add_custom_target(rapidjson DEPENDS ${EXTERN_RAPIDJSON_INCLUDE_DIR})

add_library(librapidjson INTERFACE)
add_dependencies(librapidjson rapidjson)
target_include_directories(librapidjson INTERFACE ${EXTERN_RAPIDJSON_INCLUDE_DIR})

append_third_party_library(librapidjson)
