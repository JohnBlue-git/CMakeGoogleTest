# Find google test
find_package(GTest REQUIRED)

# Fetch and Build
if (NOT GTest_FOUND)
    # Download and install GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
    )

    # CMake does not define BUILD_SHARED_LIBS by default, but projects often create a cache entry for it using the option()
    # Set BUILD_SHARED_LIBS on top level to bring it to the subdirectory
    option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
    # Re-set BUILD_SHARED_LIBS if neccessary
    #set(BUILD_SHARED_LIBS OFF)
    #message(STATUS "shared ${BUILD_SHARED_LIBS}")

    # Method 1: Make available
    FetchContent_MakeAvailable(googletest)

    # Method 2: Subdirectory
    # Populate the content
    #FetchContent_Populate(googletest)
    # Add GoogleTest as a subdirectory
    #add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Set variables
set(SOURCE
    my_test.cpp
    ${PROJECT_SOURCE_DIR}/source/caculate.cpp
)

# Set libraries runtime path
# RPATH Issues: The runtime path (RPATH) should be set correctly, or it might be stripped out during the installation process.
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Include GoogleTest headers
include_directories(
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
)

# Include project headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Add the test executable
add_executable(my_test ${SOURCE})

# Link GoogleTest and pthread
target_link_libraries(my_test PRIVATE gtest gtest_main pthread)

# Add a test
add_test(NAME my_test COMMAND my_test)
