#pragma once

#include <unordered_map>
#include "input_event_binding.hpp"



namespace input
{

class InputEventMap
{
public:
    void add(const InputEventBinding& binding)
    {
        _bindings[binding.first_input_event()].push_back(binding);
    }



    std::vector<InputEventBinding> lookup(const InputEventSequence& iseq) const
    {
        assert(!_bindings.empty());

        const auto first = iseq.front();
        const auto itr = _bindings.find(first);
        if (itr == std::end(_bindings))
        {
            return {};
        }

        std::vector<InputEventBinding> result;
        for (const auto& binding : itr->second)
        {
            if (binding.starts_with(iseq))
            {
                result.push_back(binding);
            }
        }
        return result;
    }



private:
    std::unordered_map<InputEvent, std::vector<InputEventBinding>> _bindings;
};

} // namespace input
