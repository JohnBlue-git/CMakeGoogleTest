#include <gtest/gtest.h>
#include "caculate.h"

TEST(ExampleTest, AddFunction) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}
