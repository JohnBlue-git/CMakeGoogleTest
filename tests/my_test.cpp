#include <gtest/gtest.h>
#include "caculate.h"

TEST(ExampleTest, AddFunction) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

// Main function to run all tests
// In the Google Test framework,
// we typically include the main function in your test files to initialize the Google Test framework and run all the tests.
// However, Google Test provides a default main function if you don't include one, so it's not strictly necessary.
/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
