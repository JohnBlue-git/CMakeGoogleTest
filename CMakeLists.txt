cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variable
set(BIN ${PROJECT_SOURCE_DIR}/bin)

# Add the src directory
add_subdirectory(source)

# Add the tests directory
add_subdirectory(tests)

# Define the install directory for binaries
install(TARGETS my_app DESTINATION ${BIN})
install(TARGETS my_test DESTINATION ${BIN})

# If want to install in default directoy
# the default prefix usually is is "/usr/local"
# executables and dlls would be placed in "/usr/local/bin"
# and header files folder would be placed in "/usr/local/include"
#
# ARCHIVE: static libraries .a
# LIBRARY: shared libraries .so
# RUNTIME: executables and dlls
#
#install(TARGETS <program>
#  ARCHIVE DESTINATION lib
#  LIBRARY DESTINATION lib
#  RUNTIME DESTINATION bin # For Windows DLLs
#)
#install(DIRECTORY include/ DESTINATION include)

# We can also set customized install prefix
#set(CMAKE_INSTALL_PREFIX "/desired/install/path" CACHE PATH "Installation Directory" FORCE)
#install(...)
