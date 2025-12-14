# Compile a library version for clt function plotting 
add_library(clt SHARED clt.cpp cltLink.cpp)
target_link_libraries(clt eigenpy::eigenpy)

# set the name for the clt Python extension (if needed for the Python script)
set_target_properties(clt PROPERTIES OUTPUT_NAME "clt")
set_target_properties(clt PROPERTIES PREFIX "")
set_target_properties(clt PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(clt PRIVATE ../exercise10)

