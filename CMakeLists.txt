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
