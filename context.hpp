#pragma once

#include <stack>
#include <string>


namespace input
{

struct Context
{
    std::string id;


    bool operator==(const Context& other) const
    {
        return id == other.id;
    }


    bool operator<(const Context& other) const
    {
        return id < other.id;
    }
};



struct ContextStack
{
public:
    void push(const Context& ctx)
    {
        _stack.push_back(ctx);
    }



    void pop()
    {
        if (!_stack.empty())
        {
            _stack.pop_back();
        }
    }



private:
    std::vector<Context> _stack;



public:
    using iterator = decltype(_stack)::iterator;
    using const_iterator = decltype(_stack)::const_iterator;


    iterator begin()
    {
        return std::begin(_stack);
    }

    iterator end()
    {
        return std::end(_stack);
    }


    const_iterator begin() const
    {
        return std::cbegin(_stack);
    }

    const_iterator end() const
    {
        return std::cend(_stack);
    }


    const_iterator cbegin() const
    {
        return std::cbegin(_stack);
    }

    const_iterator cend() const
    {
        return std::cend(_stack);
    }
};

} // namespace input
