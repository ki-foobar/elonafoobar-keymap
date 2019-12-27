#pragma once

#include <string>


namespace input
{

struct Action
{
    std::string id;
    std::string args;


    bool is_executable() const
    {
        return true;
    }
};

} // namespace input
