# harmonic executable
add_executable(harmonic harmonicMain.cpp harmonic.cpp)

# funks executable
add_executable(funks funksMain.cpp funks.cpp funksRange.cpp)
target_link_libraries(funks Eigen3::Eigen)

# Compile a library version with range features
add_library(funks_lib SHARED funks.cpp funksRange.cpp funksLink.cpp)
target_link_libraries(funks_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(funks_lib PROPERTIES OUTPUT_NAME "funks")
set_target_properties(funks_lib PROPERTIES PREFIX "")
set_target_properties(funks_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})

FILE(COPY plot01.py DESTINATION .)
# target_link_libraries(harmonic Eigen3::Eigen)