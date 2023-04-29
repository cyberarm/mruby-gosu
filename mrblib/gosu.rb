module Gosu
  def self.gl(z = nil, &block)
    if z
      _gl_z(z, &block)
    else
      _gl(&block)
    end
  end

  def self.render(width, height, retro: false, &block)
    _render(width, height, Gosu.image_flags(retro: retro), &block)
  end

  def self.rotate(angle, around_x = 0, around_y = 0, &block)
    _rotate(angle, around_x, around_y, &block)
  end

  def self.scale(x, y = x, around_x = 0, around_y = 0, &block)
    _scale(x, y, around_x, around_y, &block)
  end

  def self.draw_line(x1, y1, c1, x2, y2, c2, z = 0, mode = :default)
    _draw_line(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2), z, Gosu.blend_mode(mode))
  end

  def self.draw_quad(x1, y1, c1, x2, y2, c2,
                     x3, y3, c3, x4, y4, c4,
                     z = 0, mode = :default)
    _draw_quad(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2),
               x3, y3, color_to_drawop(c3), x4, y4, color_to_drawop(c4),
               z, Gosu.blend_mode(mode))
  end

  def self.draw_triangle(x1, y1, c1, x2, y2, c2, x3, y3, c3, z = 0, mode = :default)
    _draw_triangle(x1, y1, color_to_drawop(c1), x2, y2, color_to_drawop(c2),
               x3, y3, color_to_drawop(c3), z, Gosu.blend_mode(mode))
  end

  def self.draw_rect(x, y, width, height, c, z = 0, mode = :default)
    _draw_rect(x, y, width, height, color_to_drawop(c), z, Gosu.blend_mode(mode))
  end

  def self.enable_undocumented_retrofication
  end

  def self.color_to_drawop(color)
    color.is_a?(Gosu::Color) ? color.gl : color
  end

  def self.window_flags(fullscreen: false, resizable: false, borderless: false)
    flags = 0

    flags |= Gosu::WF_FULLSCREEN if fullscreen
    flags |= Gosu::WF_RESIZABLE  if resizable
    flags |= Gosu::WF_BORDERLESS if borderless

    return flags
  end

  # SEE: https://github.com/gosu/gosu/blob/master/Gosu/GraphicsBase.hpp
  def self.image_flags(retro: false, tileable: false)
    flags = 0

    flags |= Gosu::IF_RETRO if retro
    flags |= Gosu::IF_TILEABLE if tileable

    return flags
  end

  def self.font_flags(bold: false, italic: false, underline: false)
    flags = 0

    flags |= Gosu::FF_BOLD if bold
    flags |= Gosu::FF_ITALIC if italic
    flags |= Gosu::FF_UNDERLINE if underline

    return flags
  end

  def self.font_alignment_flags(mode)
    case mode
    when :left
      Gosu::AL_LEFT
    when :right
      Gosu::AL_RIGHT
    when :center
      Gosu::AL_CENTER
    when :justify
      Gosu::AL_JUSTIFY
    else
      return mode if mode.is_a?(Numeric)
      raise ArgumentError, "No such mode: #{mode}"
    end
  end

  def self.blend_mode(mode)
    case mode
    when :default
      Gosu::BM_DEFAULT
    when :additive, :add
      Gosu::BM_ADD
    when :multiply
      Gosu::BM_MULTIPLY
    else
      return mode if mode.is_a?(Numeric)
      raise ArgumentError, "No such mode: #{mode}"
    end
  end
end