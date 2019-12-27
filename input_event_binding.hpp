#pragma once

#include "action.hpp"
#include "input_event_sequence.hpp"



namespace input
{

struct InputEventBinding
{
    InputEventBinding(const InputEventSequence& events, const Action& action)
        : _events(events)
        , _action(action)
    {
    }



    const Action& action() const noexcept
    {
        return _action;
    }



    const InputEvent& first_input_event() const
    {
        return _events.front();
    }



    size_t event_sequence_size() const noexcept
    {
        return _events.size();
    }



    bool starts_with(const InputEventSequence& events) const
    {
        return _events.starts_with(events);
    }



    bool equals(const InputEventSequence& events) const
    {
        return _events == events;
    }



private:
    InputEventSequence _events;
    Action _action;
};

} // namespace input
