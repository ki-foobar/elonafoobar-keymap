class KeyBinding
  attr_reader :key_seq, :action, :context

  def initialize(key_seq, action, context=nil)
    @key_seq = key_seq
    @action = action
    @context = context
  end

  def first_key
    @key_seq.first
  end

  def call
    @action.call
  end

  def to_s
    "#{@key_seq} -> do something"
  end

  alias inspect to_s
end
