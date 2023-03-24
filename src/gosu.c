#include "Gosu.h"
#include "channel.h"
#include "color.h"
#include "font.h"
#include "image.h"
#include "mruby.h"
#include "sample.h"
#include "song.h"
#include "text_input.h"
#include "window.h"
#include "ffi_gosu.h"

struct RClass* mrb_gosu_color;
struct RClass* mrb_gosu_font;
struct RClass* mrb_gosu_image;
struct RClass* mrb_gosu_sample;
struct RClass* mrb_gosu_song;
struct RClass* mrb_gosu_channel;
struct RClass* mrb_gosu_text_input;
struct RClass* mrb_gosu_window;

static mrb_value mrb_gosu_fps(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_fps());
}

static mrb_value mrb_gosu_flush(mrb_state* mrb, mrb_value self)
{
    Gosu_flush();

    return mrb_nil_value();
}

void mrb_gosu_load_user_languages_function(void* data, const char *language)
{
    mrb_gosu_callback_data* _data = (mrb_gosu_callback_data*) data;
    mrb_value string = mrb_str_new_cstr(_data->mrb, language);

    mrb_ary_push(_data->mrb, _data->array, string);
}

static mrb_value mrb_gosu_user_languages(mrb_state* mrb, mrb_value self)
{
    mrb_value strings = mrb_ary_new(mrb);
    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.array = strings;

    Gosu_user_languages(mrb_gosu_load_user_languages_function, (void*) &data);

    return strings;
}

static mrb_value mrb_gosu_milliseconds(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_milliseconds());
}

static mrb_value mrb_gosu_default_font_name(mrb_state* mrb, mrb_value self)
{
    return mrb_str_new_cstr(mrb, Gosu_default_font_name());
}

static mrb_value mrb_gosu_button_down(mrb_state* mrb, mrb_value self)
{
    mrb_int btn_id;
    mrb_get_args(mrb, "i", &btn_id);

    return mrb_bool_value(Gosu_button_down(btn_id));
}

static mrb_value mrb_gosu_button_id_to_char(mrb_state* mrb, mrb_value self)
{
    mrb_int btn_id;
    mrb_get_args(mrb, "i", &btn_id);

    const char* string;
    string = Gosu_button_id_to_char(btn_id);

    return mrb_str_new_cstr(mrb, string);
}

static mrb_value mrb_gosu_char_to_button_id(mrb_state* mrb, mrb_value self)
{
    mrb_value string;
    mrb_get_args(mrb, "S", &string);

    const char* str;
    str = mrb_string_cstr(mrb, string);

    return mrb_fixnum_value(Gosu_button_char_to_id(str));
}

static mrb_value mrb_gosu_button_name(mrb_state* mrb, mrb_value self)
{
    mrb_int btn_id;
    mrb_get_args(mrb, "i", &btn_id);

    const char* string;
    string = Gosu_button_name(btn_id);

    return mrb_str_new_cstr(mrb, string);
}

static mrb_value mrb_gosu_gamepad_name(mrb_state* mrb, mrb_value self)
{
    mrb_int gp_id;
    mrb_get_args(mrb, "i", &gp_id);

    const char* string;
    string = Gosu_gamepad_name(gp_id);

    return mrb_str_new_cstr(mrb, string);
}

static mrb_value mrb_gosu_axis(mrb_state* mrb, mrb_value self)
{
    mrb_int gp_id;
    mrb_get_args(mrb, "i", &gp_id);

    double val;
    val = Gosu_axis(gp_id);

    return mrb_float_value(mrb, val);
}

static mrb_value mrb_gosu_draw_line(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2, z;
    mrb_int c1, c2, mode;
    mrb_get_args(mrb, "ffiffifi", &x1, &y1, &c1, &x2, &y2, &c2, &z, &mode);

    Gosu_draw_line(x1, y1, c1, x2, y2, c2, z, mode);

    return self;
}

static mrb_value mrb_gosu_draw_quad(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2, x3, y3, x4, y4, z;
    mrb_int c1, c2, c3, c4, mode;
    mrb_get_args(mrb, "ffiffiffiffifi", &x1, &y1, &c1, &x2, &y2, &c2, &x3, &y3, &c3, &x4, &y4, &c4, &z, &mode);

    Gosu_draw_quad(x1, y1, c1, x2, y2, c2, x3, y3, c3, x4, y4, c4, z, mode);

    return self;
}

static mrb_value mrb_gosu_draw_triangle(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2, x3, y3, z;
    mrb_int c1, c2, c3, mode;
    mrb_get_args(mrb, "ffiffiffifi", &x1, &y1, &c1, &x2, &y2, &c2, &x3, &y3, &c3, &z, &mode);

    Gosu_draw_triangle(x1, y1, c1, x2, y2, c2, x3, y3, c3, z, mode);

    return self;
}

static mrb_value mrb_gosu_draw_rect(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y, width, height, z;
    mrb_int c, mode;
    mrb_get_args(mrb, "ffffifi", &x, &y, &width, &height, &c, &z, &mode);

    Gosu_draw_rect(x, y, width, height, c, z, mode);

    return self;
}

void mrb_gosu_callback_function(void* ptr)
{
    mrb_gosu_callback_data* data = (mrb_gosu_callback_data*) ptr;
    mrb_funcall(data->mrb, data->block, "call", 0);
}

static mrb_value mrb_gosu_translate(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_value block;
    mrb_get_args(mrb, "ff&", &x, &y, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_translate(x, y, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_rotate(mrb_state* mrb, mrb_value self)
{
    mrb_float angle, around_x, around_y;
    mrb_value block;
    mrb_get_args(mrb, "fff&", &angle, & around_x, &around_y, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_rotate(angle, around_x, around_y, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_scale(mrb_state* mrb, mrb_value self)
{
    mrb_float scale_x, scale_y, around_x, around_y;
    mrb_value block;
    mrb_get_args(mrb, "ffff&", &scale_x, &scale_y, &around_x, &around_y, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_scale(scale_x, scale_y, around_x, around_y, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_transform(mrb_state* mrb, mrb_value self)
{
    mrb_float m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15;
    mrb_value block;
    mrb_get_args(mrb, "ffffffffffffffff&", &m0, &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11, &m12, &m13, &m14, &m15, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_transform(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_gl(mrb_state* mrb, mrb_value self)
{
    mrb_value block;
    mrb_get_args(mrb, "&", &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_gl(mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_gl_z(mrb_state* mrb, mrb_value self)
{
    mrb_value block;
    mrb_int z;
    mrb_get_args(mrb, "i&", &z, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_gl_z(z, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_render(mrb_state* mrb, mrb_value self)
{
    mrb_int width, height, flags;
    mrb_value block;
    mrb_get_args(mrb, "iii&", &width, &height, &flags, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    mrb_value pointer = mrb_cptr_value(mrb, Gosu_render(width, height, mrb_gosu_callback_function, &data, flags));

    return mrb_obj_new(mrb, mrb_gosu_image, 1, &pointer);
}

static mrb_value mrb_gosu_record(mrb_state* mrb, mrb_value self)
{
    mrb_int width, height;
    mrb_value block;
    mrb_get_args(mrb, "ii&", &width, &height, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    mrb_value pointer = mrb_cptr_value(mrb, Gosu_record(width, height, mrb_gosu_callback_function, &data));

    return mrb_obj_new(mrb, mrb_gosu_image, 1, &pointer);
}

static mrb_value mrb_gosu_clip_to(mrb_state* mrb, mrb_value self)
{
    mrb_int x, y, width, height;
    mrb_value block;
    mrb_get_args(mrb, "iiii&", &x, &y, &width, &height, &block);

    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.block = block;

    Gosu_clip_to(x, y, width, height, mrb_gosu_callback_function, &data);

    return self;
}

static mrb_value mrb_gosu_offset_x(mrb_state* mrb, mrb_value self)
{
    mrb_float angle, radius;
    mrb_get_args(mrb, "ff", &angle, &radius);

    return mrb_float_value(mrb, Gosu_offset_x(angle, radius));
}

static mrb_value mrb_gosu_offset_y(mrb_state* mrb, mrb_value self)
{
    mrb_float angle, radius;
    mrb_get_args(mrb, "ff", &angle, &radius);

    return mrb_float_value(mrb, Gosu_offset_y(angle, radius));
}

static mrb_value mrb_gosu_distance(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2;
    mrb_get_args(mrb, "ffff", &x1, &y1, &x2, &y2);

    return mrb_float_value(mrb, Gosu_distance(x1, y1, x2, y2));
}

static mrb_value mrb_gosu_angle(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2;
    mrb_get_args(mrb, "ffff", &x1, &y1, &x2, &y2);

    return mrb_float_value(mrb, Gosu_angle(x1, y1, x2, y2));
}

static mrb_value mrb_gosu_angle_diff(mrb_state* mrb, mrb_value self)
{
    mrb_float angle1, angle2;
    mrb_get_args(mrb, "ff", &angle1, &angle2);

    return mrb_float_value(mrb, Gosu_angle_diff(angle1, angle2));
}

static mrb_value mrb_gosu_random(mrb_state* mrb, mrb_value self)
{
    mrb_float min, max;
    mrb_get_args(mrb, "ff", &min, &max);

    return mrb_float_value(mrb, Gosu_random(min, max));
}

static mrb_value mrb_gosu_screen_width(mrb_state* mrb, mrb_value self)
{
    // mrb_value window_pointer;
    // mrb_get_args(mrb, "ff", &window_pointer);

    return mrb_fixnum_value(Gosu_screen_width(NULL));
}

static mrb_value mrb_gosu_screen_height(mrb_state* mrb, mrb_value self)
{
    // mrb_value window_pointer;
    // mrb_get_args(mrb, "ff", &window_pointer);

    return mrb_fixnum_value(Gosu_screen_height(NULL));
}

static mrb_value mrb_gosu_available_width(mrb_state* mrb, mrb_value self)
{
    // mrb_value window_pointer;
    // mrb_get_args(mrb, "ff", &window_pointer);

    return mrb_fixnum_value(Gosu_available_width(NULL));
}

static mrb_value mrb_gosu_available_height(mrb_state* mrb, mrb_value self)
{
    // mrb_value window_pointer;
    // mrb_get_args(mrb, "ff", &window_pointer);

    return mrb_fixnum_value(Gosu_available_height(NULL));
}

static void mrb_gosu_init(mrb_state* mrb, struct RClass* mrb_gosu)
{
    mrb_define_module_function(mrb, mrb_gosu, "fps", mrb_gosu_fps, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb_gosu, "flush", mrb_gosu_flush, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb_gosu, "user_languages", mrb_gosu_user_languages, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb_gosu, "milliseconds", mrb_gosu_milliseconds, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb_gosu, "default_font_name", mrb_gosu_default_font_name, MRB_ARGS_NONE());

    mrb_define_module_function(mrb, mrb_gosu, "button_down?", mrb_gosu_button_down, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "button_id_to_char", mrb_gosu_button_id_to_char, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "char_to_button_id", mrb_gosu_char_to_button_id, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "button_name", mrb_gosu_button_name, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "gamepad_name", mrb_gosu_gamepad_name, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "axis", mrb_gosu_axis, MRB_ARGS_REQ(1));

    mrb_define_module_function(mrb, mrb_gosu, "_draw_line", mrb_gosu_draw_line, MRB_ARGS_REQ(8));
    mrb_define_module_function(mrb, mrb_gosu, "_draw_quad", mrb_gosu_draw_quad, MRB_ARGS_REQ(14));
    mrb_define_module_function(mrb, mrb_gosu, "_draw_triangle", mrb_gosu_draw_triangle, MRB_ARGS_REQ(11));
    mrb_define_module_function(mrb, mrb_gosu, "_draw_rect", mrb_gosu_draw_rect, MRB_ARGS_REQ(7));

    mrb_define_module_function(mrb, mrb_gosu, "translate", mrb_gosu_translate, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mrb_gosu, "_rotate", mrb_gosu_rotate, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mrb_gosu, "_scale", mrb_gosu_scale, MRB_ARGS_REQ(5));
    mrb_define_module_function(mrb, mrb_gosu, "transform", mrb_gosu_transform, MRB_ARGS_REQ(17));
    mrb_define_module_function(mrb, mrb_gosu, "clip_to", mrb_gosu_clip_to, MRB_ARGS_REQ(5));

    mrb_define_module_function(mrb, mrb_gosu, "_gl", mrb_gosu_gl, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb_gosu, "_gl_z", mrb_gosu_gl_z, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb_gosu, "_render", mrb_gosu_render, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mrb_gosu, "record", mrb_gosu_record, MRB_ARGS_REQ(3));

    mrb_define_module_function(mrb, mrb_gosu, "offset_x", mrb_gosu_offset_x, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb_gosu, "offset_y", mrb_gosu_offset_y, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb_gosu, "distance", mrb_gosu_distance, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mrb_gosu, "angle", mrb_gosu_angle, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb_gosu, "angle_diff", mrb_gosu_angle_diff, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb_gosu, "random", mrb_gosu_random, MRB_ARGS_REQ(2));

    mrb_define_module_function(mrb, mrb_gosu, "screen_width", mrb_gosu_screen_width, MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mrb_gosu, "screen_height", mrb_gosu_screen_height, MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mrb_gosu, "available_width", mrb_gosu_available_width, MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mrb_gosu, "available_height", mrb_gosu_available_height, MRB_ARGS_OPT(1));
}

void mrb_mruby_gosu_gem_init(mrb_state* mrb)
{
    struct RClass* mrb_gosu;
    mrb_gosu = mrb_define_module(mrb, "Gosu");

    mrb_gosu_init(mrb, mrb_gosu);
    mrb_gosu_window_init(mrb, mrb_gosu);
    mrb_gosu_text_input_init(mrb, mrb_gosu);
    mrb_gosu_image_init(mrb, mrb_gosu);
    mrb_gosu_font_init(mrb, mrb_gosu);
    mrb_gosu_sample_init(mrb, mrb_gosu);
    mrb_gosu_song_init(mrb, mrb_gosu);
    mrb_gosu_channel_init(mrb, mrb_gosu);
    mrb_gosu_color_init(mrb, mrb_gosu);
}

void mrb_mruby_gosu_gem_final(mrb_state* mrb)
{
}