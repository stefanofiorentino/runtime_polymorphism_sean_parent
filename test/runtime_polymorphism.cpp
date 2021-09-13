#include <gmock/gmock.h>

#include <document.hpp>

class my_class_t final : public object_t
{
public: 
    void draw(std::ostream& out, size_t position) const override
    {
        out << std::string(position, ' ') << "my_class_t\n";
    }
};

void test_helper(std::ostream& out)
{    
    document_t document;

    document.emplace_back(std::make_shared<my_class_t>());

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
  my_class_t
</document>
)", oss.str());
}
