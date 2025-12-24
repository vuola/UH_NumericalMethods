# Compile a library version for verifyFiterf for function plotting 
add_library(fiterf MODULE fiterf.cpp fiterfLink.cpp)
target_link_libraries(fiterf eigenpy::eigenpy  GSL::gsl GSL::gslcblas)

# Compile a library version of evaluateFitpoly for function plotting
add_library(fitpoly MODULE fitpoly.cpp fitpolyLink.cpp)
target_link_libraries(fitpoly eigenpy::eigenpy GSL::gsl GSL::gslcblas)
    
# set the name for the verifyfiterf Python extension (if needed for the Python script)
set_target_properties(fiterf PROPERTIES OUTPUT_NAME "fiterf")
target_include_directories(fiterf PRIVATE ../exercise13)

# set the name for the evaluateFitpoly Python extension (if needed for the Python script)
set_target_properties(fitpoly PROPERTIES OUTPUT_NAME "fitpoly")
target_include_directories(fitpoly PRIVATE ../exercise13)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(fiterf)
configure_python_extension(fitpoly)

install(TARGETS fiterf
        LIBRARY DESTINATION runtime)

install(TARGETS fitpoly
        LIBRARY DESTINATION runtime)

