class Window < Gosu::Window
  def initialize
    super(500, 500, false, 16.6667, true)
  end

  def update
    self.caption = "Hello from mruby! #{Gosu.fps} fps"
  end
end

window = Window.new
window.show