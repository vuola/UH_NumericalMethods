add_executable(ex1 main.cpp)

# Link the executable with the library
# target_link_libraries(YourExecutableName PRIVATE YourLibrary::YourLibrary)

# OR IF NOT FINDING:
#
# Specify the include directory for the library's header files
# target_include_directories(YourExecutableName PRIVATE YourLibraryDirectory/include)
#
# Link the executable with the library binary
# target_link_libraries(YourExecutableName PRIVATE ${CMAKE_SOURCE_DIR}/YourLibraryDirectory/lib/yourlibrary.lib)
