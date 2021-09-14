#include <gmock/gmock.h>

#include <document.hpp>

void test_helper(std::ostream& out)
{    
    document_t document;
    document.reserve(5);

    document.emplace_back(0);
    document.emplace_back(1);
    document.emplace_back(2);
    document.emplace_back(3);
    document.emplace_back(4);

    std::reverse(std::begin(document), std::end(document));
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
  4
  3
  2
  1
  0
</document>
)", oss.str());
}
