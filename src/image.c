#include "image.h"
#include "ffi_gosu.h"

extern struct RClass* mrb_gosu_image;

typedef struct mrb_gosu_image_data_t
{
    Gosu_Image* image;
} mrb_gosu_image_data_t;

static void mrb_gosu_image_data_free(mrb_state* mrb, void* ptr)
{
    mrb_gosu_image_data_t* data = (mrb_gosu_image_data_t*) ptr;

    if (data != NULL) {
        if (data->image != NULL) {
            Gosu_Image_destroy(data->image);
        }
        mrb_free(mrb, data);
    }
}

static struct mrb_data_type const mrb_gosu_image_data_type = {
        "Image",
        mrb_gosu_image_data_free,
};

Gosu_Image* mrb_gosu_image_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_gosu_image_data_t* data = (mrb_gosu_image_data_t*) DATA_PTR(self);
    return data->image;
}

static mrb_value mrb_gosu_image_new(mrb_state* mrb, mrb_value self)
{
    mrb_value path;
    mrb_int flags;
    mrb_gosu_image_data_t* data;

    mrb_get_args(mrb, "Si", &path, &flags);

    data = (mrb_gosu_image_data_t*) DATA_PTR(self);

    if (data) {
        mrb_free(mrb, data);
    }

    DATA_TYPE(self) = &mrb_gosu_image_data_type;
    DATA_PTR(self) = NULL;

    data = (mrb_gosu_image_data_t*) mrb_malloc(mrb, sizeof(mrb_gosu_image_data_t));
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
    }
    data->image = Gosu_Image_create(mrb_string_cstr(mrb, path), flags);

    DATA_PTR(self) = data;

    return self;
}

static mrb_value mrb_gosu_image_new_from_pointer(mrb_state* mrb, mrb_value self)
{
    mrb_value pointer;
    mrb_gosu_image_data_t* data;

    mrb_get_args(mrb, "o", &pointer);

    data = (mrb_gosu_image_data_t*) DATA_PTR(self);

    if (data) {
        mrb_free(mrb, data);
    }

    DATA_TYPE(self) = &mrb_gosu_image_data_type;
    DATA_PTR(self) = NULL;

    data = (mrb_gosu_image_data_t*) mrb_malloc(mrb, sizeof(mrb_gosu_image_data_t));

    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
    }

    data->image = (Gosu_Image*) mrb_cptr(pointer);

    DATA_PTR(self) = data;

    return self;
}

static mrb_value mrb_gosu_image_from_text(mrb_state* mrb, mrb_value self)
{
    mrb_value text, font;
    mrb_float line_height, spacing;
    mrb_int width, align, font_flags, image_flags;
    mrb_get_args(mrb, "SfSifiii", &text, &line_height, &font, &width, &spacing, &align, &font_flags, &image_flags);

    Gosu_Image* pointer = Gosu_Image_create_from_text(mrb_string_cstr(mrb, text), mrb_string_cstr(mrb, font), line_height, width, spacing,
                                                      align, font_flags, image_flags);
    mrb_value image = mrb_cptr_value(mrb, pointer);

    return mrb_obj_new(mrb, mrb_gosu_image, 1, &image);
}

static mrb_value mrb_gosu_image_from_markup(mrb_state* mrb, mrb_value self)
{
    mrb_value markup, font;
    mrb_float line_height, spacing;
    mrb_int width, align, font_flags, image_flags;
    mrb_get_args(mrb, "SfSifiii", &markup, &line_height, &font, &width, &spacing, &align, &font_flags, &image_flags);

    Gosu_Image* pointer = Gosu_Image_create_from_markup(mrb_string_cstr(mrb, markup), mrb_string_cstr(mrb, font), line_height, width,
                                                        spacing, align, font_flags, image_flags);
    mrb_value image = mrb_cptr_value(mrb, pointer);

    return mrb_obj_new(mrb, mrb_gosu_image, 1, &image);
}

static mrb_value mrb_gosu_image_from_blob(mrb_state* mrb, mrb_value self)
{
    unsigned char* blob;
    mrb_int width, height, length, flags;
    mrb_get_args(mrb, "iisi", &width, &height, &blob, &length, &flags);

    Gosu_Image* image;
    image = Gosu_Image_create_from_blob(blob, length, width, height, flags);

    mrb_value pointer = mrb_cptr_value(mrb, image);

    return mrb_obj_new(mrb, mrb_gosu_image, 1, &pointer);
}

void mrb_gosu_image_load_tiles_function(void* data, Gosu_Image* image_ptr)
{
    mrb_gosu_callback_data* _data = (mrb_gosu_callback_data*) data;
    mrb_value pointer;
    pointer = mrb_cptr_value(_data->mrb, image_ptr);

    mrb_ary_push(_data->mrb, _data->array, mrb_obj_new(_data->mrb, mrb_gosu_image, 1, &pointer));
}

static mrb_value mrb_gosu_image_load_tiles(mrb_state* mrb, mrb_value self)
{
    mrb_value path;
    mrb_int tile_width, tile_height, flags;
    mrb_get_args(mrb, "Siii", &path, &tile_width, &tile_height, &flags);

    mrb_value images = mrb_ary_new(mrb);
    mrb_gosu_callback_data data;
    data.mrb = mrb;
    data.array = images;

    Gosu_Image_create_from_tiles(mrb_string_cstr(mrb, path), tile_width, tile_height, mrb_gosu_image_load_tiles_function, (void*) &data,
                                 flags);

    return images;
}

static mrb_value mrb_gosu_image_draw(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y, z, scale_x, scale_y;
    mrb_int color, mode;
    mrb_get_args(mrb, "fffffii", &x, &y, &z, &scale_x, &scale_y, &color, &mode);

    Gosu_Image_draw(mrb_gosu_image_get_ptr(mrb, self), x, y, z, scale_x, scale_y, color, mode);

    return self;
}

static mrb_value mrb_gosu_image_draw_rot(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y, z, angle, center_x, center_y, scale_x, scale_y;
    mrb_int color, mode;
    mrb_get_args(mrb, "ffffffffii", &x, &y, &z, &angle, &center_x, &center_y, &scale_x, &scale_y, &color, &mode);

    Gosu_Image_draw_rot(mrb_gosu_image_get_ptr(mrb, self), x, y, z, angle, center_x, center_y, scale_x, scale_y, color, mode);

    return self;
}

static mrb_value mrb_gosu_image_draw_as_quad(mrb_state* mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2, x3, y3, x4, y4, z;
    mrb_int c1, c2, c3, c4, mode;
    mrb_get_args(mrb, "ffiffiffiffifi", &x1, &y1, &c1, &x2, &y2, &c2, &x3, &y3, &c3, &x4, &y4, &c4, &z, &mode);

    Gosu_Image_draw_as_quad(mrb_gosu_image_get_ptr(mrb, self), x1, y1, c1, x2, y2, c2, x3, y3, c3, x4, y4, c4, z, mode);

    return self;
}

static mrb_value mrb_gosu_image_width(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Image_width(mrb_gosu_image_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_image_height(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Image_height(mrb_gosu_image_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_image_save(mrb_state* mrb, mrb_value self)
{
    mrb_value path;
    mrb_get_args(mrb, "S", &path);

    Gosu_Image_save(mrb_gosu_image_get_ptr(mrb, self), mrb_str_to_cstr(mrb, path));

    return self;
}

static mrb_value mrb_gosu_image_to_blob(mrb_state* mrb, mrb_value self)
{
    size_t length;
    Gosu_Image* image;
    image = mrb_gosu_image_get_ptr(mrb, self);
    length = Gosu_Image_width(image) * Gosu_Image_height(image) * 4; // Gosu::Color is 4 bytes

    return mrb_str_new(mrb, (const char*) Gosu_Image_to_blob(image), length);
}

static mrb_value mrb_gosu_image_insert(mrb_state* mrb, mrb_value self)
{
    mrb_value other_image;
    mrb_int x, y;
    mrb_get_args(mrb, "oii", &other_image, &x, &y);

    Gosu_Image_insert(mrb_gosu_image_get_ptr(mrb, self), mrb_gosu_image_get_ptr(mrb, other_image), x, y);

    return self;
}

void mrb_gosu_image_init(mrb_state* mrb, struct RClass* mrb_gosu)
{
    mrb_gosu_image = mrb_define_class_under(mrb, mrb_gosu, "Image", mrb->object_class);

    mrb_define_class_method(mrb, mrb_gosu_image, "_load_tiles", mrb_gosu_image_load_tiles, MRB_ARGS_REQ(4));
    mrb_define_class_method(mrb, mrb_gosu_image, "_from_blob", mrb_gosu_image_from_blob, MRB_ARGS_REQ(4));
    mrb_define_class_method(mrb, mrb_gosu_image, "_from_text", mrb_gosu_image_from_text, MRB_ARGS_REQ(8));
    mrb_define_class_method(mrb, mrb_gosu_image, "_from_markup", mrb_gosu_image_from_markup, MRB_ARGS_REQ(8));

    mrb_define_method(mrb, mrb_gosu_image, "_new", mrb_gosu_image_new, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, mrb_gosu_image, "_new_from_pointer", mrb_gosu_image_new_from_pointer, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, mrb_gosu_image, "_draw", mrb_gosu_image_draw, MRB_ARGS_REQ(7));
    mrb_define_method(mrb, mrb_gosu_image, "_draw_rot", mrb_gosu_image_draw_rot, MRB_ARGS_REQ(10));
    mrb_define_method(mrb, mrb_gosu_image, "_draw_as_quad", mrb_gosu_image_draw_as_quad, MRB_ARGS_REQ(14));

    mrb_define_method(mrb, mrb_gosu_image, "width", mrb_gosu_image_width, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_image, "height", mrb_gosu_image_height, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_image, "save", mrb_gosu_image_save, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_image, "to_blob", mrb_gosu_image_to_blob, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_image, "insert", mrb_gosu_image_insert, MRB_ARGS_REQ(2));
}

void mrb_gosu_image_free(mrb_state* mrb, mrb_value self)
{
}