# Compile a library version for clt function plotting 
add_library(clt MODULE clt.cpp cltLink.cpp)
target_link_libraries(clt eigenpy::eigenpy)

# set the name for the clt Python extension (if needed for the Python script)
set_target_properties(clt PROPERTIES OUTPUT_NAME "clt")
target_include_directories(clt PRIVATE ../exercise10)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(clt)

install(TARGETS clt
        LIBRARY DESTINATION runtime)