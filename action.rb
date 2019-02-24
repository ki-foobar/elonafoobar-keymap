class Action
  def initialize(&block)
    @callback = block
  end

  def call
    @callback.call()
  end
end
