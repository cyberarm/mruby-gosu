module Gosu
  def self.render(width, height, retro: false, &block)
    _render(width, height, block, Gosu.image_flags(retro: retro))
  end

  def self.rotate(angle, around_x = 0, around_y = 0, &block)
    _rotate(angle, around_x, around_y, block)
  end

  def self.scale(x, y, around_x = 0, around_y = 0, &block)
    _scale(x, y, around_x, around_y, block)
  end

  def self.draw_line(x1, y1, c1, x2, y2, c2, z = 0, mode = :default)
    _draw_line(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2), z, Gosu.blendmode(mode))
  end

  def self.draw_quad(x1, y1, c1, x2, y2, c2,
                     x3, y3, c3, x4, y4, c4,
                     z = 0, mode = :default)
    _draw_quad(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2),
               x3, y3, color_to_drawop(c3), x4, y4, color_to_drawop(c4),
               z, Gosu.blendmode(mode))
  end

  def self.draw_triangle(x1, y1, c1, x2, y2, c2, x3, y3, c3, z = 0, mode = :default)
    _draw_triangle(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2),
               x3, y3, color_to_drawop(c3), z, Gosu.blendmode(mode))
  end

  def self.draw_rect(x, y, width, height, c, z = 0, mode = :default)
    _draw_rect(x, y, width, height, color_to_drawop(c), z, Gosu.blendmode(mode))
  end

  def self.enable_undocumented_retrofication
  end

  def self.color_to_drawop(color)
    color.is_a?(Gosu::Color) ? color.gl : color
  end

  # SEE: https://github.com/gosu/gosu/blob/master/Gosu/GraphicsBase.hpp
  def self.image_flags(retro: false, tileable: false)
    flags = 0x0

    flags |= 1 << 5 if retro
    flags |= 1 << 8 if tileable

    return flags
  end

  def self.font_flags(bold: false, italic: false, underline: false)
    flags = 0x0
    flags |= 1 if bold
    flags |= 2 if italic
    flags |= 4 if underline

    return flags
  end

  def self.font_alignment_flags(mode)
    case mode
    when :left
      0
    when :right
      1
    when :center
      2
    when :justify
      3
    else
      return mode if mode.is_a?(Numeric)
      raise ArgumentError, "No such mode: #{mode}"
    end
  end

  def self.blendmode(mode)
    case mode
    when :default
      0
    when :additive, :add
      1
    when :multiply
      2
    else
      return mode if mode.is_a?(Numeric)
      raise ArgumentError, "No such mode: #{mode}"
    end
  end
end