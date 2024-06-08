#include <gtest/gtest.h>

// 示例测试案例
TEST(SampleTest, Case1) {
    EXPECT_EQ(1, 1);
}

TEST(SampleTest, Case2) {
    EXPECT_TRUE(true);
}

// 主函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
