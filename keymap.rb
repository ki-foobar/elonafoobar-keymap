class Keymap
  attr_reader :mode

  def initialize(mode)
    @mode = mode
    @key_bindings = {}
  end

  def register(key_binding)
    (@key_bindings[key_binding.first_key] ||= []) << key_binding
  end

  def lookup(key_seq)
    raise if key_seq.empty?

    first = key_seq.first
    result = []

    unless @key_bindings[first]
      return []
    end

    @key_bindings[first].each do |kb|
      # start-with match
      if kb.key_seq.start_with?(key_seq)
        result << kb
      end
    end
    result
  end
end
