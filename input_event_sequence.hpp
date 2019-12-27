#pragma once

#include <vector>
#include "input_event.hpp"



namespace input
{

struct InputEventSequence
{
    InputEventSequence()
    {
    }



    InputEventSequence(std::initializer_list<InputEvent>&& events)
        : _events(events)
    {
    }



    const InputEvent& front() const
    {
        return _events.front();
    }



    bool starts_with(const InputEventSequence& other) const
    {
        if (_events.size() < other._events.size())
        {
            return false;
        }
        else
        {
            for (size_t i = 0; i < other._events.size(); ++i)
            {
                if (other._events[i] != _events[i])
                {
                    return false;
                }
            }
            return true;
        }
    }



    void push_back(const InputEvent& k)
    {
        _events.push_back(k);
    }



    size_t size() const noexcept
    {
        return _events.size();
    }



    void clear()
    {
        _events.clear();
    }



    bool operator==(const InputEventSequence& other) const
    {
        return std::equal(
            std::begin(_events), std::end(_events), std::begin(other._events));
    }



private:
    std::vector<InputEvent> _events;



public:
    using iterator = decltype(_events)::iterator;
    using const_iterator = decltype(_events)::const_iterator;


    iterator begin()
    {
        return std::begin(_events);
    }

    iterator end()
    {
        return std::end(_events);
    }


    const_iterator begin() const
    {
        return std::cbegin(_events);
    }

    const_iterator end() const
    {
        return std::cend(_events);
    }


    const_iterator cbegin() const
    {
        return std::cbegin(_events);
    }

    const_iterator cend() const
    {
        return std::cend(_events);
    }
};

} // namespace input
