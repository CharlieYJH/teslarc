add_library(third_party INTERFACE)

# Appends a third party library onto the list of libraries
function(append_third_party_library lib)
    target_link_libraries(third_party INTERFACE ${lib})
endfunction(append_third_party_library)

# Extract and build each third party dependency
add_subdirectory("curl")
add_subdirectory("rapidjson")
