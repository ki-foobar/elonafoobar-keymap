class KeySequence
  def initialize(*keys)
    @keys = keys
  end

  def <<(new_key)
    @keys << new_key
  end

  def first
    @keys.first
  end

  def eql?(other)
    keys == other.keys
  end

  alias == eql?

  def to_s
    @keys.join
  end

  def size
    @keys.size
  end

  def empty?
    @keys.empty?
  end

  def start_with?(other)
    if size < other.size
      false
    else
      other.keys.each_with_index do |k, i|
        if k != keys[i]
          return false
        end
      end
      true
    end
  end

  def each(&block)
    @keys.each(&block)
  end

  protected

  attr_reader :keys
end
