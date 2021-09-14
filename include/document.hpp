#pragma once

#include <iostream>
#include <memory>

void draw(const int& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << x << "\n";
}

class object_t {
public: 
    object_t(int x) : self_(std::make_unique<int_model_t>(std::move(x))) {}

    object_t(const object_t& x) : self_(std::make_unique<int_model_t>(*x.self_)) {}
    object_t(object_t&&) noexcept = default;

    object_t& operator=(const object_t& x) noexcept
    { return *this = object_t(x); }
    object_t& operator=(object_t&&) noexcept = default;
    
    friend void draw(const object_t&x, std::ostream& out, size_t position)
    { x.self_->draw(out, position); }
private: 
    struct int_model_t
    {
        int_model_t(int x) : data_(std::move(x)){}
        void draw(std::ostream& out, size_t position) const
        {
            ::draw(data_, out, position);
        }
        int data_;
    };
    std::unique_ptr<int_model_t> self_;
};

using document_t = std::vector<object_t>;

void draw(const document_t& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "<document>\n" ;
    for (const auto& e: x) draw(e, out, position + 2);
    out << std::string(position, ' ') << "</document>\n" ;
}
