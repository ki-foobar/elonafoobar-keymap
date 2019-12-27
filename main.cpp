#include <cassert>
#include <iostream>
#include "input_event_handler.hpp"

using namespace input;

constexpr int rawkey_x = 'x';
constexpr int rawkey_y = 'y';
constexpr int rawkey_z = 'z';
constexpr int rawkey_timeout = '\0';

InputEvent key_x{rawkey_x, 0};
InputEvent key_y{rawkey_y, 0};
InputEvent key_z{rawkey_z, 0};
InputEvent timeout{rawkey_timeout, 0};


template <typename... Args>
InputEventSequence Q(Args&&... args)
{
    return {std::forward<Args>(args)...};
}


Action A(const char* id)
{
    return {id, ""};
}


void test()
{
    InputEventHandler h;

    Context g{"global"};
    Context m{"menu"};

    h.bind(g, Q(key_x), A("x"));
    h.bind(g, Q(key_x, key_x), A("xx"));
    h.bind(g, Q(key_x, key_y), A("xy"));
    h.bind(g, Q(key_z), A("z"));
    h.bind(m, Q(key_y), A("m__y"));

    h.push_context(g);

    {
        h.handle_event(key_x);
        const auto a1 = h.get_action();
        assert(a1.id == "__empty__");
    }
    {
        h.handle_event(key_x);
        const auto a1 = h.get_action();
        assert(a1.id == "xx");
        const auto a2 = h.get_action();
        assert(a2.id == "__empty__");
    }

    {
        h.handle_event(key_x);
        const auto a1 = h.get_action();
        assert(a1.id == "__empty__");
    }
    {
        h.handle_event(key_y);
        const auto a1 = h.get_action();
        assert(a1.id == "xy");
        const auto a2 = h.get_action();
        assert(a2.id == "__empty__");
    }

    {
        h.handle_event(key_x);
        const auto a1 = h.get_action();
        assert(a1.id == "__empty__");
    }
    {
        h.handle_event(key_z);
        const auto a1 = h.get_action();
        assert(a1.id == "x");
        const auto a2 = h.get_action();
        assert(a2.id == "z");
        const auto a3 = h.get_action();
        assert(a3.id == "__empty__");
    }

    {
        h.handle_event(key_x);
        const auto a1 = h.get_action();
        assert(a1.id == "__empty__");
    }
    {
        h.handle_event(timeout);
        const auto a1 = h.get_action();
        assert(a1.id == "x");
        const auto a2 = h.get_action();
        assert(a2.id == "__empty__");
    }

    h.push_context(m);
    {
        h.handle_event(key_y);
        const auto a1 = h.get_action();
        assert(a1.id == "m__y");
    }
    {
        h.handle_event(key_z);
        const auto a1 = h.get_action();
        assert(a1.id == "z");
    }

    std::cout << "All tests succeeded!" << std::endl;
}



int main()
{
    test();
}
