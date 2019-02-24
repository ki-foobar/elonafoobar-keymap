require './keymap.rb'

class KeyEventDispatcher
  def initialize
    @keymaps = {}
    @pending_key_seq = KeySequence.new
  end

  def create_keymap(mode)
    keymap = Keymap.new(mode)
    register_keymap(keymap)
  end

  def register_keymap(keymap)
    @keymaps[keymap.mode] = keymap
  end

  def mode=(new_mode)
    @current_mode = new_mode
  end

  def handle(key, max = 9999)
    @pending_key_seq << key
    keymaps = find_active_keymaps
    candidates = []
    keymaps.each do |keymap|
      key_bindings = keymap.lookup(@pending_key_seq)
      candidates += key_bindings
    end
    longest = 0
    candidates.each do |kb|
      if kb.key_seq.size <= max && longest < kb.key_seq.size
        longest = kb.key_seq.size
      end
    end
    tmp = []
    candidates.each do |kb|
      if kb.key_seq.size == longest
        tmp << kb
      end
    end
    candidates = tmp
    if candidates.empty?
      if @pending_key_seq.size == 1
        @pending_key_seq = KeySequence.new
        puts "No action"
      else
        key_seq = @pending_key_seq
        @pending_key_seq = KeySequence.new
        key_seq.each do |key|
          handle(key, key_seq.size - 1)
        end
      end
    elsif candidates.size == 1 && candidates.first.key_seq == @pending_key_seq
      key_binding = candidates.first
      key_binding.call
      @pending_key_seq = KeySequence.new
    end
  end

  def find_active_keymaps
    [@keymaps[@current_mode]]
  end
end
