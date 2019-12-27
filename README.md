Proof of concept

Algorithm to map multiple input events to actions.


## Terms

- Input event
  - One raw event (e.g., key press, mouse down, etc)
- Input event sequence
  - Sequence of input events
- Input event binding
  - Input event sequence, action and context
- Input event map
  - List of input event bindings
- Input event handler
  - Dictionary of input event map and context
- Action
  - Unique identifier with arguments
- Context
  - Identifier to distinguish each context
- Context stack
  - Stack of contexts


## Tests

See `main.cpp` for details.

Bindings:

- `x` => action x
- `x`, `x` => action xx
- `x`, `y` => action xy
- `z` => action z

Input:

- `x`, `x` => action xx
- `x`, `y` => action xy
- `x`, `z` => action x, action z
- `x`, timeout => action x
