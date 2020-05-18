module Gosu
  def self.enable_undocumented_retrofication
  end

  def self.color_to_drawop(color)
    # color.is_a?(Gosu::Color) ? color.gl : color
    color
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