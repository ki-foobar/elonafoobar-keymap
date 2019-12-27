#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <queue>
#include "context.hpp"
#include "input_event_map.hpp"



namespace input
{

namespace detail
{

template <typename Range, typename Predicate>
void filter_inplace(Range&& r, Predicate p)
{
    // r.erase(
    //     std::remove_if(std::begin(r), std::end(r), std::not_fn(p)),
    //     std::end(r));
    r.erase(
        std::remove_if(
            std::begin(r), std::end(r), [&](const auto& x) { return !p(x); }),
        std::end(r));
}

} // namespace detail



class InputEventHandler
{
public:
    void handle_event(const InputEvent& event)
    {
        handle_event_internal(event, 99);
    }



    void bind(
        const Context& ctx,
        const InputEventSequence& events,
        const Action& action)
    {
        add_binding(ctx, {events, action});
    }



    void add_binding(const Context& ctx, const InputEventBinding& binding)
    {
        _event_map_table[ctx].add(binding);
    }



    // std::optional<Action> get_action()
    // {
    //     if (_action_queue.empty())
    //     {
    //         return std::nullopt;
    //     }
    //     else
    //     {
    //         const auto ret = _action_queue.front();
    //         _action_queue.pop();
    //         return ret;
    //     }
    // }
    Action get_action()
    {
        if (_action_queue.empty())
        {
            return Action{"__empty__", ""};
        }
        else
        {
            const auto ret = _action_queue.front();
            _action_queue.pop();
            return ret;
        }
    }



    void put_action(const Action& action)
    {
        _action_queue.push(action);
    }



    // Clear the current pending input events and the action queue.
    void clear()
    {
        _pending_input_events.clear();

        // Clear the action queue by swapping with an empty container.
        // std::queue does not have clear() method for some reason.
        decltype(_action_queue) tmp;
        std::swap(_action_queue, tmp);
    }



    void push_context(const Context& ctx)
    {
        _context_stack.push(ctx);
    }



    void pop_context()
    {
        _context_stack.pop();
    }



private:
    std::map<Context, InputEventMap> _event_map_table;
    InputEventSequence _pending_input_events;
    std::queue<Action> _action_queue;
    ContextStack _context_stack;



    void handle_event_internal(
        const InputEvent& event,
        size_t max_event_sequence_length)
    {
        _pending_input_events.push_back(event);

        const auto candidates =
            make_candidates(_pending_input_events, max_event_sequence_length);
        if (candidates.empty())
        {
            // There is no binding which start with the current pending
            // event sequence.
            if (_pending_input_events.size() == 1)
            {
                // Immediately it turns out that there is surely no action.
                _pending_input_events.clear();
                // put_action(Action::no_action);
            }
            else
            {
                // These events could be interpreted as smaller fragments.
                const auto events = _pending_input_events;
                _pending_input_events.clear();
                for (const auto& event : events)
                {
                    handle_event_internal(event, events.size() - 1);
                }
            }
        }
        else if (
            candidates.size() == 1 &&
            candidates.front().equals(_pending_input_events))
        {
            // Okay, it is the very action we need.
            put_action(candidates.front().action());
            _pending_input_events.clear();
        }
        else
        {
            assert(1 < candidates.size());
            // Failed to determine the action, you need input more events.
        }
    }



    // Returns a set of bindings which start with @a event_sequence and have
    // longest length.
    std::vector<InputEventBinding> make_candidates(
        const InputEventSequence& event_sequence,
        size_t max_event_sequence_length)
    {
        for (const auto& ctx : _context_stack)
        {
            if (_event_map_table.find(ctx) == std::end(_event_map_table))
                continue;

            auto ret = _event_map_table[ctx].lookup(event_sequence);
            // Since all binding has at least 1-length input event sequence, it
            // is safe to set zero to `longest` as an initial value.
            size_t longest = 0;
            for (const auto& binding : ret)
            {
                if (binding.event_sequence_size() <=
                        max_event_sequence_length &&
                    longest < binding.event_sequence_size())
                {
                    longest = binding.event_sequence_size();
                }
            }

            detail::filter_inplace(ret, [=](const auto& binding) {
                return binding.event_sequence_size() == longest &&
                    binding.action().is_executable();
            });

            if (!ret.empty())
            {
                return ret;
            }
        }

        return {};
    }
};

} // namespace input
