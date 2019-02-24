class Key
  attr_reader :base, :modifiers

  def initialize(base, modifiers=nil)
    @base = base
    @modifiers = modifiers
  end

  def eql?(other)
    base == other.base && modifiers == other.modifiers
  end

  alias == eql?

  def hash
    "#{base}__#{modifiers}".hash
  end

  def to_s
    if has_any_modifiers?
      "#{base}"
    else
      "#{base}__#{modifiers}"
    end
  end

  alias inspect to_s

  def has_any_modifiers?
    !@modifiers
  end
end
