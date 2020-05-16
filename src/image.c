#include "image.h"

struct RClass *mrb_gosu_image;

typedef struct mrb_gosu_image_data_t
{
  Gosu_Image *image;
} mrb_gosu_image_data_t;

static void
mrb_gosu_image_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_image_data_t *data = (mrb_gosu_image_data_t *)ptr;

  if (data != NULL)
  {
    if (data->image != NULL)
    {
      Gosu_Image_destroy(data->image);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_image_data_type = {
    "Image",
    mrb_gosu_image_data_free,
};

Gosu_Image *
mrb_gosu_image_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_image_data_t *data = DATA_PTR(self);
  return data->image;
}

mrb_value
mrb_gosu_image_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_bool tilable, retro;
  mrb_gosu_image_data_t *data;

  mrb_get_args(mrb, "Sbb", &path, &tilable, &retro);

  data = (mrb_gosu_image_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_image_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_image_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_image_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->image = Gosu_Image_create(mrb_string_cstr(mrb, path), 0);

  DATA_PTR(self) = data;

  return self;
}

void
mrb_gosu_image_draw(mrb_state *mrb, mrb_value self) {
  mrb_float x, y, z, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "fffffii", &x, &y, &z, &scale_x, &scale_y, &color, &mode);

  Gosu_Image_draw(mrb_gosu_image_get_ptr(mrb, self), x, y, z, scale_x, scale_y, color, mode);
}

void
mrb_gosu_image_draw_rot(mrb_state *mrb, mrb_value self) {
  mrb_float x, y, z, angle, center_x, center_y, scale_x, scale_y;
  mrb_int color, mode;
  mrb_get_args(mrb, "ffffffffii", &x, &y, &z, &angle, &center_x, &center_y, &scale_x, &scale_y, &color, &mode);

  Gosu_Image_draw_rot(mrb_gosu_image_get_ptr(mrb, self), x, y, z, angle, center_x, center_y, scale_x, scale_y, color, mode);
}

void
mrb_gosu_image_draw_as_quad(mrb_state *mrb, mrb_value self) {
  mrb_float x1, y1, x2, y2, x3, y3, x4, y4, z;
  mrb_int c1, c2, c3, c4, mode;
  mrb_get_args(mrb, "ffiffiffiffifi", &x1, &y1, &c1, &x2, &y2, &c2, &x3, &y3, &c3, &x4, &y4, &c4, &z, &mode);

  Gosu_Image_draw_as_quad(mrb_gosu_image_get_ptr(mrb, self), x1, y1, c1, x2, y2, c2, x3, y3, c3, x4, y4, c4, z, mode);
}

mrb_value
mrb_gosu_image_width(mrb_state *mrb, mrb_value self) {
  return mrb_fixnum_value( Gosu_Image_width(mrb_gosu_image_get_ptr(mrb, self)) );
}

mrb_value
mrb_gosu_image_height(mrb_state *mrb, mrb_value self) {
  return mrb_fixnum_value( Gosu_Image_height(mrb_gosu_image_get_ptr(mrb, self)) );
}

void
mrb_gosu_image_save(mrb_state *mrb, mrb_value self) {
  mrb_value path;
  mrb_get_args(mrb, "S", &path);

  Gosu_Image_save(mrb_gosu_image_get_ptr(mrb, self), mrb_str_to_cstr(mrb, path));
}

mrb_value
mrb_gosu_image_to_blob(mrb_state *mrb, mrb_value self) {
  // TODO: see if mruby can handle unsigned char
  return mrb_str_new_cstr(mrb, Gosu_Image_to_blob(mrb_gosu_image_get_ptr(mrb, self)));
}

void
mrb_gosu_image_insert(mrb_state *mrb, mrb_value self) {
  mrb_value other_image;
  mrb_int x, y;
  mrb_get_args(mrb, "oii", &other_image, &x, &y);

  Gosu_Image_insert(mrb_gosu_image_get_ptr(mrb, self), mrb_gosu_image_get_ptr(mrb, other_image), x, y);
}

void mrb_gosu_image_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_image = mrb_define_class_under(mrb, mrb_gosu, "Image", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_image, "initialize", mrb_gosu_image_initialize, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_gosu_image, "draw", mrb_gosu_image_draw, MRB_ARGS_REQ(7));
  mrb_define_method(mrb, mrb_gosu_image, "draw_rot", mrb_gosu_image_draw_rot, MRB_ARGS_REQ(10));
  mrb_define_method(mrb, mrb_gosu_image, "draw_as_quad", mrb_gosu_image_draw_as_quad, MRB_ARGS_REQ(14));

  mrb_define_method(mrb, mrb_gosu_image, "width", mrb_gosu_image_width, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_image, "height", mrb_gosu_image_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_image, "save", mrb_gosu_image_save, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_image, "to_blob", mrb_gosu_image_to_blob, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_image, "insert", mrb_gosu_image_insert, MRB_ARGS_REQ(2));
}

void mrb_gosu_image_free(mrb_state *mrb, mrb_value self)
{
}