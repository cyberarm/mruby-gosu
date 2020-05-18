#include "font.h"

struct RClass *mrb_gosu_font;

typedef struct mrb_gosu_font_data_t
{
  Gosu_Font *font;
} mrb_gosu_font_data_t;

static void
mrb_gosu_font_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_font_data_t *data = (mrb_gosu_font_data_t *)ptr;

  if (data != NULL)
  {
    if (data->font != NULL)
    {
      Gosu_Font_destroy(data->font);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_font_data_type = {
    "Font",
    mrb_gosu_font_data_free,
};

Gosu_Font *
mrb_gosu_font_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_font_data_t *data = DATA_PTR(self);
  return data->font;
}

mrb_value
mrb_gosu_font_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_int height, flags;
  mrb_gosu_font_data_t *data;

  mrb_get_args(mrb, "iSi", &height, &path, &flags);

  data = (mrb_gosu_font_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_font_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_font_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_font_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->font = Gosu_Font_create(height, mrb_string_cstr(mrb, path), 0);

  DATA_PTR(self) = data;

  return self;
}

mrb_value
mrb_gosu_font_name(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr( mrb, Gosu_Font_name(mrb_gosu_font_get_ptr(mrb, self)) );
}

mrb_value
mrb_gosu_font_height(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Gosu_Font_height(mrb_gosu_font_get_ptr(mrb, self)) );
}

mrb_value
mrb_gosu_font_flags(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Gosu_Font_flags(mrb_gosu_font_get_ptr(mrb, self)) );
}

mrb_value
mrb_gosu_font_text_width(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_get_args(mrb, "S", &string);

  Gosu_Font_text_width(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string));

  return self;
}

mrb_value
mrb_gosu_font_markup_width(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_get_args(mrb, "S", &string);

  Gosu_Font_markup_width(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string));

  return self;
}

mrb_value
mrb_gosu_font_draw_text(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_float x, y, z, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "Sfffffii", &string, &x, &y, &z, &scale_x, &scale_y, &color, &mode);

  Gosu_Font_draw_text(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string), x, y, z, scale_x, scale_y, color, mode);

  return self;
}

mrb_value
mrb_gosu_font_draw_markup(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_float x, y, z, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "Sfffffii", &string, &x, &y, &z, &scale_x, &scale_y, &color, &mode);

  Gosu_Font_draw_markup(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string), x, y, z, scale_x, scale_y, color, mode);

  return self;
}

mrb_value
mrb_gosu_font_draw_text_rel(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_float x, y, z, rel_x, rel_y, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "Sfffffffii", &string, &x, &y, &z, &rel_x, &rel_y, &scale_x, &scale_y, &color, &mode);

  Gosu_Font_draw_text_rel(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string), x, y, z, rel_x, rel_y, scale_x, scale_y, color, mode);

  return self;
}

mrb_value
mrb_gosu_font_draw_markup_rel(mrb_state *mrb, mrb_value self)
{
  mrb_value string;
  mrb_float x, y, z, rel_x, rel_y, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "Sfffffffii", &string, &x, &y, &z, &rel_x, &rel_y, &scale_x, &scale_y, &color, &mode);

  Gosu_Font_draw_markup_rel(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string), x, y, z, rel_x, rel_y, scale_x, scale_y, color, mode);

  return self;
}

mrb_value
mrb_gosu_font_set_image(mrb_state *mrb, mrb_value self)
{
  mrb_value string, image;
  mrb_int flags;
  mrb_get_args(mrb, "Sio", &string, &flags, &image);

  Gosu_Font_set_image(mrb_gosu_font_get_ptr(mrb, self), mrb_string_cstr(mrb, string), flags, mrb_gosu_image_get_ptr(mrb, image));

  return self;
}

void mrb_gosu_font_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_font = mrb_define_class_under(mrb, mrb_gosu, "Font", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_font, "_new", mrb_gosu_font_initialize, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_gosu_font, "name", mrb_gosu_font_name, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_font, "height", mrb_gosu_font_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_font, "flags", mrb_gosu_font_flags, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_gosu_font, "text_width", mrb_gosu_font_text_width, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_font, "markup_width", mrb_gosu_font_markup_width, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_gosu_font, "_draw_text", mrb_gosu_font_draw_text, MRB_ARGS_REQ(8));
  mrb_define_method(mrb, mrb_gosu_font, "_draw_markup", mrb_gosu_font_draw_markup, MRB_ARGS_REQ(8));
  mrb_define_method(mrb, mrb_gosu_font, "_draw_text_rel", mrb_gosu_font_draw_text_rel, MRB_ARGS_REQ(10));
  mrb_define_method(mrb, mrb_gosu_font, "_draw_markup_rel", mrb_gosu_font_draw_markup_rel, MRB_ARGS_REQ(10));

  mrb_define_method(mrb, mrb_gosu_font, "_set_image", mrb_gosu_font_set_image, MRB_ARGS_REQ(3));
}