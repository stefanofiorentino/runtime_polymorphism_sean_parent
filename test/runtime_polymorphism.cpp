#include <gmock/gmock.h>

#include <document.hpp>

struct my_class_t {};

void draw(const my_class_t&, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "my_class_t" << "\n";
}

void test_helper(std::ostream& out)
{    
    document_t document;
    document.reserve(5);

    document.emplace_back(0);
    document.emplace_back(std::string("Hello!"));
    document.emplace_back(2);
    document.emplace_back(my_class_t());
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
  my_class_t
  2
  Hello!
  0
</document>
)", oss.str());
}
