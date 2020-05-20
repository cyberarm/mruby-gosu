

class TestFont < MTest::Unit::TestCase
  include TestHelper

  SINGLE_PIXEL = Gosu::Image.from_blob(1, 1, "\xff\xff\xff\xff")

  def test_markup_parsing
    font = Gosu::Font.new(20)
    assert_equal 0, font.text_width("<b>")
    assert_not_equal 0, font.markup_width("<b>")
  end

  def test_custom_characters
    font = Gosu::Font.new(20)
    font["a"] = SINGLE_PIXEL
    font["b"] = SINGLE_PIXEL
    font["c"] = SINGLE_PIXEL
    # Five square letters will be scaled up to 20px.
    assert_equal 100, font.text_width("abcba")
  end

  def test_constructor_args
    bold_font = Gosu::Font.new(7, bold: true)
    regular_font = Gosu::Font.new(7, bold: false)

    assert_not_equal bold_font.text_width("Afdslkgjd"), regular_font.text_width("Afdslkgjd")
    assert_not_equal bold_font.text_width("Afdslkgjd"), regular_font.text_width("<b>Afdslkgjd</b>")

    assert_equal bold_font.text_width("Afdslkgjd"), regular_font.markup_width("<b>Afdslkgjd</b>")
    assert_equal bold_font.markup_width("</b>Afdslkgjd"), regular_font.text_width("Afdslkgjd")
  end

  def test_draw_and_draw_rel
    font = Gosu::Font.new(10, name: media_path("daniel.otf"))

    assert_output_matches "test_font/draw_markup", 0.98, [200, 100] do
      # draw this string repeatedly to make up for opacity differences in OpenGL renderers.
      255.times do
        font.draw_markup "Hi! <c=f00>Red.\r\nNew   line! Äöß\n", 5, 5, -6, 2.0, 4.0, 0xff_ff00ff, :add
      end
    end

    assert_output_matches "test_font/draw_markup_rel", 0.98, [100, 100] do
      # draw this string repeatedly to make up for opacity differences in OpenGL renderers.
      255.times do
        font.draw_markup_rel "<c=000>I &lt;3 Ruby/Gosu!\n", 50, 50, 5, 0.4, -2
      end
    end
  end
end