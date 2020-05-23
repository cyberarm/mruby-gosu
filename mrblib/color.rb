module Gosu
  class Color
    def self.argb(*args)
      Gosu::Color.new(*args)
    end

    def self.rgba(r, g, b, a)
      Gosu::Color.new(a, r, g, b)
    end

    def self.rgb(r, g, b)
      Gosu::Color.new(255, r, g, b)
    end

    def self.from_ahsv(alpha, h, s, v)
      Gosu::Color.new(Color._color_from_ahsv(alpha.clamp(0.0, 255.0), h % 360.0, s.clamp(0.0, 1.0), v.clamp(0.0, 1.0)))
    end

    def self.from_hsv(h, s, v)
      Gosu::Color.new(Color._color_from_hsv(h % 360.0, s.clamp(0.0, 1.0), v.clamp(0.0, 1.0)))
    end

    def initialize(*args)
      if args.size == 1
        @color = Color._color_from_integer(args.first)
      elsif args.size == 4
        _args = args.map { |i| i.clamp(0, 255) }
        @color = Color._color_from_argb(*_args)
      else
        raise "Error"
      end
    end

    def alpha
      Color._color_alpha(@color)
    end

    def alpha=(value)
      @color = Color._color_set_alpha(@color, value.clamp(0, 255))
    end

    def red
      Color._color_red(@color)
    end

    def red=(value)
      @color = Color._color_set_red(@color, value.clamp(0, 255))
    end

    def green
      Color._color_green(@color)
    end

    def green=(value)
      @color = Color._color_set_green(@color, value.clamp(0, 255))
    end

    def blue
      Color._color_blue(@color)
    end

    def blue=(value)
      @color = Color._color_set_blue(@color, value.clamp(0, 255))
    end

    def value
      Color._color_value(@color)
    end

    def value=(value)
      @color = Color._color_set_value(@color, value.clamp(0.0, 1.0))
    end

    def saturation
      Color._color_saturation(@color)
    end

    def saturation=(value)
      @color = Color._color_set_saturation(@color, value.clamp(0.0, 1.0))
    end

    def hue
      Color._color_hue(@color)
    end

    def hue=(value)
      @color = Color._color_set_hue(@color, value % 360.0)
    end

    def bgr
      Color._color_bgr(@color)
    end

    def abgr
      Color._color_abgr(@color)
    end

    def argb
      Color._color_argb(@color)
    end

    def gl
      @color
    end

    def ==(other)
      gl == other&.gl
    end

    def <(other)
      gl < other.gl
    end

    def >(other)
      gl > other.gl
    end

    alias hash gl
    def eql?(other)
      self == other
    end

    NONE = Gosu::Color.argb(0x00_000000)
    BLACK = Gosu::Color.argb(0xff_000000)
    GRAY = Gosu::Color.argb(0xff_808080)
    WHITE = Gosu::Color.argb(0xff_ffffff)
    AQUA = Gosu::Color.argb(0xff_00ffff)
    RED = Gosu::Color.argb(0xff_ff0000)
    GREEN = Gosu::Color.argb(0xff_00ff00)
    BLUE = Gosu::Color.argb(0xff_0000ff)
    YELLOW = Gosu::Color.argb(0xff_ffff00)
    FUCHSIA = Gosu::Color.argb(0xff_ff00ff)
    CYAN = Gosu::Color.argb(0xff_00ffff)
  end
end