#include "window.h"
#include "text_input.h"

extern struct RClass* mrb_gosu_window;
extern struct RClass* mrb_gosu_text_input;

typedef struct mrb_gosu_window_callback
{
    mrb_state* mrb;
    mrb_value self;
} mrb_gosu_window_callback;

typedef struct mrb_gosu_window_data_t
{
    Gosu_Window* window;
    mrb_value text_input;
} mrb_gosu_window_data_t;

static void mrb_gosu_window_data_free(mrb_state* mrb, void* ptr)
{
    mrb_gosu_window_data_t* data = (mrb_gosu_window_data_t*) ptr;

    if (data != NULL) {
        if (data->window != NULL) {
            Gosu_Window_destroy(data->window);
        }
        mrb_free(mrb, data);
    }
}

static struct mrb_data_type const mrb_gosu_window_data_type = {
        "Window",
        mrb_gosu_window_data_free,
};

Gosu_Window* mrb_gosu_window_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_gosu_window_data_t* data = (mrb_gosu_window_data_t*) DATA_PTR(self);
    return data->window;
}

static void mrb_gosu_window_update_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "update", 0);
}

static void mrb_gosu_window_draw_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "draw", 0);
}

static void mrb_gosu_window_button_down_callback(void* data, unsigned int btn_id)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "button_down", 1, mrb_fixnum_value(btn_id));
}

static void mrb_gosu_window_button_up_callback(void* data, unsigned int btn_id)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "button_up", 1, mrb_fixnum_value(btn_id));
}

static void mrb_gosu_window_drop_callback(void* data, const char* filename)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "drop", 1, mrb_str_new_cstr(mrb, filename));
}

static bool mrb_gosu_window_needs_redraw_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    return mrb_bool(mrb_funcall(mrb, self, "needs_redraw?", 0));
}

static bool mrb_gosu_window_needs_cursor_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    return mrb_bool(mrb_funcall(mrb, self, "needs_cursor?", 0));
}

static void mrb_gosu_window_close_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "close", 0);
}

static void mrb_gosu_window_gamepad_connected_callback(void* data, int index)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "gamepad_connected", 1, mrb_fixnum_value(index));
}

static void mrb_gosu_window_gamepad_disconnected_callback(void* data, int index)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "gamepad_disconnected", 1, mrb_fixnum_value(index));
}

static void mrb_gosu_window_gain_focus_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "gain_focus", 0);
}

static void mrb_gosu_window_lose_focus_callback(void* data)
{
    mrb_gosu_window_callback* callback = (mrb_gosu_window_callback*) data;
    mrb_state* mrb = callback->mrb;
    mrb_value self = callback->self;

    mrb_funcall(mrb, self, "lose_focus", 0);
}

static mrb_value mrb_gosu_window_show(mrb_state* mrb, mrb_value self)
{
    Gosu_Window_show(mrb_gosu_window_get_ptr(mrb, self));

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_tick(mrb_state* mrb, mrb_value self)
{
    Gosu_Window_tick(mrb_gosu_window_get_ptr(mrb, self));

    return self;
}

static mrb_value mrb_gosu_window_caption(mrb_state* mrb, mrb_value self)
{
    const char* _caption = Gosu_Window_caption(mrb_gosu_window_get_ptr(mrb, self));

    return mrb_str_new(mrb, _caption, strlen(_caption));
}

static mrb_value mrb_gosu_window_set_caption(mrb_state* mrb, mrb_value self)
{
    mrb_value caption;
    const int argc = mrb_get_args(mrb, "S", &caption);
    if (argc != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
    }

    Gosu_Window_set_caption(mrb_gosu_window_get_ptr(mrb, self), mrb_string_value_cstr(mrb, &caption));

    return self;
}

static mrb_value mrb_gosu_window_width(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Window_width(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_set_width(mrb_state* mrb, mrb_value self)
{
    mrb_int width;
    mrb_get_args(mrb, "i", &width);

    Gosu_Window_set_width(mrb_gosu_window_get_ptr(mrb, self), width);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_height(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Window_height(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_set_height(mrb_state* mrb, mrb_value self)
{
    mrb_int height;
    mrb_get_args(mrb, "i", &height);

    Gosu_Window_set_height(mrb_gosu_window_get_ptr(mrb, self), height);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_update_interval(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Window_update_interval(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_set_update_interval(mrb_state* mrb, mrb_value self)
{
    mrb_float interval;
    mrb_get_args(mrb, "f", &interval);

    Gosu_Window_set_update_interval(mrb_gosu_window_get_ptr(mrb, self), interval);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_default_button_down(mrb_state* mrb, mrb_value self)
{
    mrb_int id;
    mrb_get_args(mrb, "i", &id);

    Gosu_Window_default_button_down(mrb_gosu_window_get_ptr(mrb, self), id);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_mouse_x(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Window_mouse_x(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_set_mouse_x(mrb_state* mrb, mrb_value self)
{
    mrb_int point;
    mrb_get_args(mrb, "i", &point);

    Gosu_Window_set_mouse_x(mrb_gosu_window_get_ptr(mrb, self), point);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_mouse_y(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(Gosu_Window_mouse_y(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_set_mouse_y(mrb_state* mrb, mrb_value self)
{
    mrb_int point;
    mrb_get_args(mrb, "i", &point);

    Gosu_Window_set_mouse_y(mrb_gosu_window_get_ptr(mrb, self), point);

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_is_fullscreen(mrb_state* mrb, mrb_value self)
{
    return mrb_bool_value(Gosu_Window_is_fullscreen(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_is_resizable(mrb_state* mrb, mrb_value self)
{
    return mrb_bool_value(Gosu_Window_is_resizable(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_is_borderless(mrb_state* mrb, mrb_value self)
{
    return mrb_bool_value(Gosu_Window_is_borderless(mrb_gosu_window_get_ptr(mrb, self)));
}

static mrb_value mrb_gosu_window_text_input(mrb_state* mrb, mrb_value self)
{
    Gosu_TextInput* text_input;
    text_input = Gosu_Window_text_input(mrb_gosu_window_get_ptr(mrb, self));

    if (text_input != NULL) {
        mrb_gosu_window_data_t* data = (mrb_gosu_window_data_t*) DATA_PTR(self);
        return data->text_input;
    }
    else {
        return mrb_nil_value();
    }
}

static mrb_value mrb_gosu_window_set_text_input(mrb_state* mrb, mrb_value self)
{
    mrb_value text_input;
    mrb_get_args(mrb, "o", &text_input);

    if (!mrb_nil_p(text_input)) {
        Gosu_Window_set_text_input(mrb_gosu_window_get_ptr(mrb, self), mrb_gosu_text_input_get_ptr(mrb, text_input));
    }
    else {
        Gosu_Window_set_text_input(mrb_gosu_window_get_ptr(mrb, self), NULL);
    }

    mrb_value old_text_input;
    mrb_gosu_window_data_t* data = (mrb_gosu_window_data_t*) DATA_PTR(self);
    old_text_input = data->text_input;

    if (mrb_obj_is_kind_of(mrb, old_text_input, mrb_gosu_text_input)) {
        mrb_gc_unregister(mrb, old_text_input);
    }

    if (mrb_obj_is_kind_of(mrb, text_input, mrb_gosu_text_input)) {
        mrb_gc_register(mrb, text_input);
    }

    data->text_input = text_input;

    return mrb_nil_value();
}

static mrb_value mrb_gosu_window_close_immediately(mrb_state* mrb, mrb_value self)
{
    Gosu_Window_close_immediately(mrb_gosu_window_get_ptr(mrb, self));

    return self;
}

static mrb_value mrb_gosu_window_new(mrb_state* mrb, mrb_value self)
{
    mrb_int width, height;
    mrb_float update_interval;
    mrb_int window_flags;
    mrb_gosu_window_data_t* data;

    int const argc = mrb_get_args(mrb, "iiif", &width, &height, &window_flags, &update_interval);
    if (argc != 4) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
    }

    data = (mrb_gosu_window_data_t*) DATA_PTR(self);

    if (data) {
        mrb_free(mrb, data);
    }

    DATA_TYPE(self) = &mrb_gosu_window_data_type;
    DATA_PTR(self) = NULL;

    data = (mrb_gosu_window_data_t*) mrb_malloc(mrb, sizeof(mrb_gosu_window_data_t));
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
    }

    data->window = Gosu_Window_create(width, height, window_flags, update_interval);

    DATA_PTR(self) = data;

    // TODO: This should probably be refactored in future
    static mrb_gosu_window_callback callback;
    callback.mrb = mrb;
    callback.self = self;

    Gosu_Window_set_update(data->window, mrb_gosu_window_update_callback, &callback);
    Gosu_Window_set_draw(data->window, mrb_gosu_window_draw_callback, &callback);
    Gosu_Window_set_button_down(data->window, mrb_gosu_window_button_down_callback, &callback);
    Gosu_Window_set_button_up(data->window, mrb_gosu_window_button_up_callback, &callback);
    Gosu_Window_set_drop(data->window, mrb_gosu_window_drop_callback, &callback);
    Gosu_Window_set_needs_redraw(data->window, mrb_gosu_window_needs_redraw_callback, &callback);
    Gosu_Window_set_needs_cursor(data->window, mrb_gosu_window_needs_cursor_callback, &callback);
    Gosu_Window_set_gamepad_connected(data->window, mrb_gosu_window_gamepad_connected_callback, &callback);
    Gosu_Window_set_gamepad_disconnected(data->window, mrb_gosu_window_gamepad_disconnected_callback, &callback);
    Gosu_Window_set_gain_focus(data->window, mrb_gosu_window_gain_focus_callback, &callback);
    Gosu_Window_set_lose_focus(data->window, mrb_gosu_window_lose_focus_callback, &callback);
    Gosu_Window_set_close(data->window, mrb_gosu_window_close_callback, &callback);

    return self;
}

void mrb_gosu_window_init(mrb_state* mrb, struct RClass* mrb_gosu)
{
    mrb_gosu_window = mrb_define_class_under(mrb, mrb_gosu, "Window", mrb->object_class);

    mrb_define_method(mrb, mrb_gosu_window, "_new", mrb_gosu_window_new, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, mrb_gosu_window, "caption", mrb_gosu_window_caption, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "caption=", mrb_gosu_window_set_caption, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "width", mrb_gosu_window_width, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "width=", mrb_gosu_window_set_width, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "height", mrb_gosu_window_height, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "height=", mrb_gosu_window_set_height, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "update_interval", mrb_gosu_window_update_interval, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "update_interval=", mrb_gosu_window_set_update_interval, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "_default_button_down", mrb_gosu_window_default_button_down, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "mouse_x", mrb_gosu_window_mouse_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "mouse_x=", mrb_gosu_window_set_mouse_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "mouse_y", mrb_gosu_window_mouse_y, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "mouse_y=", mrb_gosu_window_set_mouse_y, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "fullscreen?", mrb_gosu_window_is_fullscreen, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "resizable?", mrb_gosu_window_is_resizable, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "borderless?", mrb_gosu_window_is_borderless, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "text_input", mrb_gosu_window_text_input, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "text_input=", mrb_gosu_window_set_text_input, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_gosu_window, "show", mrb_gosu_window_show, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "tick", mrb_gosu_window_tick, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_gosu_window, "close!", mrb_gosu_window_close_immediately, MRB_ARGS_NONE());
}

void mrb_gosu_window_free(mrb_state* mrb, mrb_value self)
{
}