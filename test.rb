require './action.rb'
require './context.rb'
require './key.rb'
require './keybinding.rb'
require './keyeventdispatcher.rb'
require './keysequence.rb'
require './mode.rb'

dispatcher = KeyEventDispatcher.new
mode = Mode.new('core', 'menu')
keymap = dispatcher.create_keymap(mode)

key_seq = KeySequence.new(Key.new(:x))
action = Action.new { puts "X" }
key_binding = KeyBinding.new(key_seq, action)
keymap.register(key_binding)

key_seq = KeySequence.new(Key.new(:x), Key.new(:x))
action = Action.new { puts "XX" }
key_binding = KeyBinding.new(key_seq, action)
keymap.register(key_binding)

key_seq = KeySequence.new(Key.new(:x), Key.new(:y))
action = Action.new { puts "XY" }
key_binding = KeyBinding.new(key_seq, action)
keymap.register(key_binding)

key_seq = KeySequence.new(Key.new(:z))
action = Action.new { puts "Z" }
key_binding = KeyBinding.new(key_seq, action)
keymap.register(key_binding)

dispatcher.mode = mode

dispatcher.handle(Key.new(:x))
dispatcher.handle(Key.new(:x)) # => XX

dispatcher.handle(Key.new(:x))
dispatcher.handle(Key.new(:y)) # => XY

dispatcher.handle(Key.new(:x))
dispatcher.handle(Key.new(:z)) # => X, Z

dispatcher.handle(Key.new(:z)) # => Z

dispatcher.handle(Key.new(:y)) #=> No action

dispatcher.handle(Key.new(:x))
dispatcher.handle(Key.new(:timeout)) #=> X, no action
