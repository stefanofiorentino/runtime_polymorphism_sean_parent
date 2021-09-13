#include <gmock/gmock.h>

#include <document.hpp>

TEST(runtime_polymorphism, basic_unit_test)
{
    document_t document;

    document.emplace_back(0);
    document.emplace_back(1);
    document.emplace_back(2);
    document.emplace_back(3);
    document.emplace_back(4);

    std::ostringstream oss;
    draw(document, oss, 0);

    ASSERT_EQ(R"(<document>
  0
  1
  2
  3
  4
</document>
)", oss.str());
}
