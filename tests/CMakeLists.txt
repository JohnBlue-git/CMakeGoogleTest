# Find google test
find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    # Download and install GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Set variables
set(SOURCE
    my_test.cpp
    ${PROJECT_SOURCE_DIR}/source/caculate.cpp
)

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
target_link_libraries(my_test gtest gtest_main pthread)

# Add a test
add_test(NAME my_test COMMAND my_test)
