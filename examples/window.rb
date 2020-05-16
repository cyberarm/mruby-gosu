class Window < Gosu::Window
  def initialize
    super(500, 500, false, 16.6667, true)
  end

  def draw
    Gosu.draw_line(0, 0, 0xffff5500, 500, 500, 0xff00ffff, 0, 0)
    Gosu.draw_quad(
      100, 0, 0x55ffffff,
      200, 0, 0x550055ff,
      100, 200, 0x55ff55ff,
      0, 200, 0x555555ff,
      0, 0
    )
    Gosu.draw_triangle(
      0, 0, 0x55ffffff,
      500, 0, 0x550055ff,
      250, 500, 0x55ff55ff,
      0, 0
    )
    Gosu.draw_rect(0, 0, 500, 500, 0x55ff00ff, 0, 0)
  end

  def update
    self.caption = "Hello from mruby! #{Gosu.fps} fps"
  end

  def needs_cursor?
    true
  end

  def drop(filename)
    puts filename
  end
end

window = Window.new
window.show