class Window < Gosu::Window
  def initialize
    super(500, 500, false, 16.6667, false)

    self.caption = "Hello from mruby!"
  end

  def update
    puts "Called!"
    self.caption = Gosu.fps
  end
end

window = Window.new
window.show