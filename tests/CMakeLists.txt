# Download and install GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Include GoogleTest headers
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add the test executable
add_executable(my_test my_test.cpp)

# Link GoogleTest and pthread
target_link_libraries(my_test gtest gtest_main pthread)

# Add a test
add_test(NAME my_test COMMAND my_test)
