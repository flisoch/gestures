#include "gtest/gtest.h"

TEST(SquareRootTest, PositiveNos) { 
    int i = 18;
    EXPECT_EQ(18, i);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
