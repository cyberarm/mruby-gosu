class Window < Gosu::Window
  def initialize
    super 500, 500, resizable: true

    @font = Gosu::Font.new(56, name: Gosu.default_font_name)

    @square = Gosu::Image.from_blob(10, 10, "\xff\xff\xff\x88" * 100)
    @square_color = Gosu::Color.new(0xff_ffffff)
  end

  def draw
    Gosu.draw_line(0, 0, 0xffff5500, 500, 500, 0xff00ffff)
    Gosu.draw_quad(
      100, 0, 0x55ffffff,
      200, 0, 0x550055ff,
      100, 200, 0x55ff55ff,
      0, 200, 0x555555ff
    )
    Gosu.draw_triangle(
      0, 0, 0x55ffffff,
      500, 0, 0x550055ff,
      250, 500, 0x55ff55ff
    )
    Gosu.draw_rect(0, 0, 500, 500, 0x55ff00ff)

    @square.draw(mouse_x - 10, mouse_y - 10, 10, 1, 1, @square_color)

    @font.draw_markup("<b>Hello</b> <c=f80>World</c>", 10, 10, 2, 1, 1, 0x55ff8844)
  end

  def update
    self.caption = "Hello from mruby! #{Gosu.fps} fps"

    @square_color.alpha = Math.sin(Gosu.milliseconds / 1000.0).abs * 255.0
  end

  def needs_cursor?
    true
  end
end

window = Window.new
window.show