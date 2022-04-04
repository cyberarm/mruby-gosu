module Gosu
  class Image
    def self.load_tiles(path, tile_width, tile_height, tileable: false, retro: false)
      _load_tiles(path, tile_width, tile_height, Gosu.image_flags(tileable: tileable, retro: retro))
    end

    def self.from_blob(width, height, blob = "\0\0\0\0" * (width * height), tileable: false, retro: false)
      _from_blob(width, height, blob, Gosu.image_flags(tileable: tileable, retro: retro))
    end

    def self.from_text(text, line_height, font: Gosu.default_font_name, width: -1, spacing: 0, align: :left,
                       bold: false, italic: false, underline: false, retro: false)
      _from_text(text.to_s, line_height, font, width, spacing,
                 Gosu.font_alignment_flags(align), Gosu.font_flags(bold: bold, italic: italic, underline: underline), Gosu.image_flags(retro: retro))
    end

    def self.from_markup(markup, line_height, font: Gosu.default_font_name, width: -1, spacing: 0, align: :left,
                       bold: false, italic: false, underline: false, retro: false)
      _from_markup(markup.to_s, line_height, font, width, spacing,
                   Gosu.font_alignment_flags(align), Gosu.font_flags(bold: bold, italic: italic, underline: underline), Gosu.image_flags(retro: retro))
    end

    def initialize(source, tileable: false, retro: false)
      if source.is_a?(String)
        _new(source, Gosu.image_flags(tileable: tileable, retro: retro))
      elsif source.respond_to?(:to_blob) &&
            source.respond_to?(:columns) &&
            source.respond_to?(:row)
        _from_blob(source.width, source.height, source.to_blob, Gosu.image_flags(tileable: tileable, retro: retro))
      else
        _new_from_pointer(source)
      end
    end

    def draw(x, y, z, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw(x, y, z, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blend_mode(mode))
    end

    def draw_rot(x, y, z, angle, center_x = 0.5, center_y = 0.5, scale_x = 1, scale_y = 1, color = 0xff_ffffff, mode = :default)
      _draw_rot(x, y, z, angle, center_x, center_y, scale_x, scale_y, Gosu.color_to_drawop(color), Gosu.blend_mode(mode))
    end

    def draw_as_quad(x1, y1, color1, x2, y2, color2, x3, y3, color3, x4, y4, color4, z = 0, mode = :default)
      _draw_as_quad(x1, y1, Gosu.color_to_drawop(color1), x2, y2, Gosu.color_to_drawop(color2),
                    x3, y3, Gosu.color_to_drawop(color3), x4, y4, Gosu.color_to_drawop(color4),
                    z, Gosu.blend_mode(mode))
    end
  end
end