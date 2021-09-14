#include <gmock/gmock.h>

#include <document.hpp>

void test_helper(std::ostream& out)
{    
    document_t document;

    document.emplace_back(0);
    document.emplace_back(1);
    document.emplace_back(2);
    document.emplace_back(3);
    document.emplace_back(4);

    draw(document, out, 0);
}

struct TestFixture : ::testing::Test
{
    std::ostringstream oss;
};

TEST_F(TestFixture, runtime_polymorphism)
{
    test_helper(oss);
    ASSERT_EQ(R"(<document>
  0
  1
  2
  3
  4
</document>
)", oss.str());
}
