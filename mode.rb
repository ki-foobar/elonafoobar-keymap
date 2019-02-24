class Mode
  attr_reader :mod, :name

  def initialize(mod, name)
    @mod = mod
    @name = name
  end

  def eql?(other)
    mod == other.mod && name == other.name
  end

  def hash
    "#{mod}__#{name}".hash
  end
end
