# Compile a library version for verifyFiterf for function plotting 
add_library(fiterf SHARED fiterf.cpp fiterfLink.cpp)
target_link_libraries(fiterf eigenpy::eigenpy  GSL::gsl GSL::gslcblas)
    
# set the name for the verifyfiterf Python extension (if needed for the Python script)
set_target_properties(fiterf PROPERTIES OUTPUT_NAME "fiterf")
set_target_properties(fiterf PROPERTIES PREFIX "")
set_target_properties(fiterf PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(fiterf PRIVATE ../exercise13)

