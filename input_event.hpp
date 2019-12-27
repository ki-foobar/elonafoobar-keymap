#pragma once

#include <utility>



namespace input
{

struct InputEvent
{
    int raw;
    int modifiers;

    bool operator==(const InputEvent& rhs) const noexcept
    {
        return raw == rhs.raw && modifiers == rhs.modifiers;
    }

    bool operator!=(const InputEvent& rhs) const noexcept
    {
        return !(*this == rhs);
    }
};

} // namespace input



namespace std
{

template <>
struct hash<::input::InputEvent>
{
    size_t operator()(const ::input::InputEvent& e) const
    {
        return std::hash<int>{}(e.raw) ^ std::hash<int>{}(e.modifiers);
    }
};

} // namespace std
