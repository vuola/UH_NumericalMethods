add_library(matrix SHARED matrix.cpp)

target_link_libraries(matrix eigenpy::eigenpy)
set_target_properties(matrix PROPERTIES PREFIX "")
set_target_properties(matrix PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})

FILE(COPY test_matrix.py DESTINATION .)



