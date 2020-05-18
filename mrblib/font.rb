module Gosu
  class Font
    def initialize(height, name: Gosu.default_font_name, bold: false, italic: false, underline: false)
      _new(height, name, Gosu.font_flags(bold: bold, italic: italic, underline: underline))
    end

    def draw_text(text, x, y, z, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw_text(text.to_s, x, y, z, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blendmode(mode))
    end

    def draw_markup(text, x, y, z, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw_markup(text.to_s, x, y, z, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blendmode(mode))
    end

    def draw_text_rel(text, x, y, z, rel_x, rel_y, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw_text_rel(text.to_s, x, y, z, rel_x, rel_y, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blendmode(mode))
    end

    def draw_markup_rel(text, x, y, z, rel_x, rel_y, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw_markup_rel(text.to_s, x, y, z, rel_x, rel_y, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blendmode(mode))
    end

    def []=(codepoint, image)
      _set_image(codepoint, self.flags, image)
    end
  end
end