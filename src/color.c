#include "color.h"

struct RClass *mrb_gosu_color;

static mrb_value
mrb_gosu_color_create(mrb_state *mrb, mrb_value self)
{
  mrb_int i;
  mrb_get_args(mrb, "i", &i);

  return mrb_fixnum_value(Gosu_Color_create(i));
}

static mrb_value
mrb_gosu_color_create_argb(mrb_state *mrb, mrb_value self)
{
  mrb_int a, r, g, b;
  mrb_get_args(mrb, "iiii", &a, &r, &g, &b);

  return mrb_fixnum_value(Gosu_Color_create_argb(a, r, g, b));
}

static mrb_value
mrb_gosu_color_create_ahsv(mrb_state *mrb, mrb_value self)
{
  mrb_int a, h, s, v;
  mrb_get_args(mrb, "iiii", &a, &h, &s, &v);

  return mrb_fixnum_value(Gosu_Color_create_from_ahsv(a, h, s, v));
}

static mrb_value
mrb_gosu_color_create_hsv(mrb_state *mrb, mrb_value self)
{
  mrb_int h, s, v;
  mrb_get_args(mrb, "iii", &h, &s, &v);

  return mrb_fixnum_value(Gosu_Color_create_from_hsv(h, s, v));
}

static mrb_value
mrb_gosu_color_alpha(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_alpha(color));
}

static mrb_value
mrb_gosu_color_red(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_red(color));
}

static mrb_value
mrb_gosu_color_green(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_green(color));
}

static mrb_value
mrb_gosu_color_blue(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_blue(color));
}

static mrb_value
mrb_gosu_color_set_alpha(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_alpha(color, value));
}

static mrb_value
mrb_gosu_color_set_red(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_red(color, value));
}

static mrb_value
mrb_gosu_color_set_green(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_green(color, value));
}

static mrb_value
mrb_gosu_color_set_blue(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_blue(color, value));
}

static mrb_value
mrb_gosu_color_value(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_float_value(mrb, Gosu_Color_value(color));
}

static mrb_value
mrb_gosu_color_saturation(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_float_value(mrb, Gosu_Color_saturation(color));
}

static mrb_value
mrb_gosu_color_hue(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_float_value(mrb, Gosu_Color_hue(color));
}

static mrb_value
mrb_gosu_color_set_value(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_value(color, value));
}

static mrb_value
mrb_gosu_color_set_saturation(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_saturation(color, value));
}

static mrb_value
mrb_gosu_color_set_hue(mrb_state *mrb, mrb_value self)
{
  mrb_int color, value;
  mrb_get_args(mrb, "ii", &color, &value);

  return mrb_fixnum_value(Gosu_Color_set_hue(color, value));
}

static mrb_value
mrb_gosu_color_bgr(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_bgr(color));
}

static mrb_value
mrb_gosu_color_abgr(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_abgr(color));
}

static mrb_value
mrb_gosu_color_argb(mrb_state *mrb, mrb_value self)
{
  mrb_int color;
  mrb_get_args(mrb, "i", &color);

  return mrb_fixnum_value(Gosu_Color_argb(color));
}

void mrb_gosu_color_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_color = mrb_define_class_under(mrb, mrb_gosu, "Color", mrb->object_class);

  mrb_define_class_method(mrb, mrb_gosu_color, "_color_from_integer", mrb_gosu_color_create,      MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_from_argb",    mrb_gosu_color_create_argb, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_from_ahsv",    mrb_gosu_color_create_ahsv, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_from_hsv",     mrb_gosu_color_create_hsv,  MRB_ARGS_REQ(3));

  mrb_define_class_method(mrb, mrb_gosu_color, "_color_alpha",     mrb_gosu_color_alpha,     MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_alpha", mrb_gosu_color_set_alpha, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_red",       mrb_gosu_color_red,       MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_red",   mrb_gosu_color_set_red,   MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_green",     mrb_gosu_color_green,     MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_green", mrb_gosu_color_set_green, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_blue",      mrb_gosu_color_blue,      MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_blue",  mrb_gosu_color_set_blue,  MRB_ARGS_REQ(2));

  mrb_define_class_method(mrb, mrb_gosu_color, "_color_value",          mrb_gosu_color_value,          MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_value",      mrb_gosu_color_set_value,      MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_saturation",     mrb_gosu_color_saturation,     MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_saturation", mrb_gosu_color_set_saturation, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_hue",            mrb_gosu_color_hue,            MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_set_hue",        mrb_gosu_color_set_hue,        MRB_ARGS_REQ(2));

  mrb_define_class_method(mrb, mrb_gosu_color, "_color_bgr",  mrb_gosu_color_bgr,  MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_abgr", mrb_gosu_color_abgr, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mrb_gosu_color, "_color_argb", mrb_gosu_color_argb, MRB_ARGS_REQ(1));
}