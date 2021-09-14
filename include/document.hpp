#pragma once

#include <iostream>
#include <memory>

template <typename T>
void draw(const T& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << x << "\n";
}

class object_t {
public: 
    template <typename T>
    object_t(T x) : self_(std::make_unique<model_t<T>>(std::move(x))) {}

    object_t(const object_t& x) : self_(x.self_->copy_()) {}
    object_t(object_t&&) noexcept = default;

    object_t& operator=(const object_t& x) noexcept
    { return *this = object_t(x); }
    object_t& operator=(object_t&&) noexcept = default;
    
    friend void draw(const object_t&x, std::ostream& out, size_t position)
    { x.self_->draw(out, position); }
private: 
    struct concept_t
    {
        virtual ~concept_t() = default;
        virtual std::unique_ptr<concept_t> copy_() const = 0;
        virtual void draw(std::ostream& out, size_t position) const = 0;
    };
    template <typename T>
    struct model_t final : concept_t
    {
        model_t(T x) : data_(std::move(x)){}
        std::unique_ptr<concept_t> copy_() const override 
        { return std::make_unique<model_t<T>>(*this); }
        void draw(std::ostream& out, size_t position) const override
        {
            ::draw(data_, out, position);
        }
        T data_;
    };
    std::unique_ptr<concept_t> self_;
};

using document_t = std::vector<object_t>;

void draw(const document_t& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "<document>\n" ;
    for (const auto& e: x) draw(e, out, position + 2);
    out << std::string(position, ' ') << "</document>\n" ;
}
