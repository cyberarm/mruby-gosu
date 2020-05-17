class Window < Gosu::Window
  def initialize
    super(500, 500, false, 16.6667, true)

    @angle = 0
    @last_time = Gosu.milliseconds
    @mruby_logo = Gosu::Image.new("/home/cyberarm/Code/mruby/doc/mruby_logo_red_icon.png", 0, 0)
    @image = Gosu::Image.new("/home/cyberarm/Downloads/Untitled.png", 0, 0)

    @mruby_logo.insert(@image, 50, 50)
    @mruby_logo.save("logo.png")

    p @image.to_blob

    @font = Gosu::Font.new(56, Gosu.default_font_name, 0)
    self.text_input = Gosu::TextInput.new
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

    @mruby_logo.draw_rot(width / 2, height / 2,1, @angle, 0.5, 0.5, 1,1, 0x88ffffff, 0)
    @image.draw_rot(width / 4 * 3, height / 4 * 3,1, -@angle, 0.5, 0.5, 4,4, 0x88ffffff, 0)

    @font.draw_markup("<b>Hello</b> <c=f80>World</c>", 10, 10, 2, 1, 1, 0x55ff8844, 0)
    if text_input.respond_to?(:text)
      @font.draw_text(text_input.text, 10, 72, 2, 1, 1, 0xffffffff, 0)
    end
  end

  def update
    self.caption = "Hello from mruby! #{Gosu.fps} fps"
    @angle += 45.0 * (Gosu.milliseconds - @last_time) / 1000.0
    @angle %= 360.0
    @last_time = Gosu.milliseconds
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