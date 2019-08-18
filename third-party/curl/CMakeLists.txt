set(EXTERN_CURL_VERSION 7.62.0)
set(
    EXTERN_CURL_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/curl-${EXTERN_CURL_VERSION}/include"
    CACHE STRING "curl include directory"
    FORCE
)
set(
    EXTERN_CURL_LIBRARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/curl-${EXTERN_CURL_VERSION}/lib/.libs/libcurl.a"
    CACHE STRING "curl static library"
    FORCE
)

add_custom_command(
    OUTPUT ${EXTERN_CURL_INCLUDE_DIR}
    COMMAND tar --skip-old-files -xzf "${CMAKE_CURRENT_SOURCE_DIR}/curl-${EXTERN_CURL_VERSION}.tar.gz"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/curl-${EXTERN_CURL_VERSION}.tar.gz"
    COMMENT "Unpacking curl"
    VERBATIM
)

add_custom_command(
    OUTPUT ${EXTERN_CURL_LIBRARY_DIR}
    COMMAND ./configure --enable-static --disable-shared
    COMMAND $(MAKE)
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/curl-${EXTERN_CURL_VERSION}"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/curl-${EXTERN_CURL_VERSION}"
    COMMENT "Building curl"
    VERBATIM
)

add_custom_target(curl
    DEPENDS ${EXTERN_CURL_INCLUDE_DIR}
            ${EXTERN_CURL_LIBRARY_DIR}
)

add_library(libcurl INTERFACE)
add_dependencies(libcurl curl)
target_include_directories(libcurl INTERFACE ${EXTERN_CURL_INCLUDE_DIR})
target_link_libraries(libcurl INTERFACE ${EXTERN_CURL_LIBRARY_DIR} pthread ssl crypto)

append_third_party_library(libcurl)
