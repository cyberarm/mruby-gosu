#include "window.h"

struct RClass *mrb_gosu_window;

typedef struct mrb_gosu_window_data_t {
  Gosu_Window *window;
} mrb_gosu_window_data_t;

static void
mrb_gosu_window_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_window_data_t *data = (mrb_gosu_window_data_t*)ptr;

  if (data != NULL) {
    if (data->window != NULL) {
      Gosu_Window_destroy(data->window);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type
const mrb_gosu_window_data_type = {
  "Window", mrb_gosu_window_data_free,
};

Gosu_Window*
mrb_gosu_window_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_window_data_t *data = DATA_PTR(self);
  return data->window;
}

static mrb_value
mrb_gosu_window_set_update(mrb_state *mrb, mrb_value self)
{
  mrb_method_t method;
  method = mrb_method_search_vm(mrb, mrb_gosu_window, "update");

  if (method != NULL) {
    mrb_funcall(mrb, self, "update", 0);
  }

  return self;
}

static mrb_value
mrb_gosu_window_set_draw(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_button_down(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_button_up(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_drop(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_needs_redraw(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_needs_cursor(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_set_close(mrb_state *mrb, mrb_value self)
{
  mrb_method_t m;

  m = mrb_method_search_vm(mrb, &mrb_gosu_window, "close");
  if (MRB_METHOD_UNDEF_P(m)) {
    Gosu_Window_close_immediately(mrb_gosu_window_get_ptr(mrb, self));
    mrb_name_error(mrb, "close", "undefined method '%n' for class %C", "close", mrb_gosu_window);
  } else {
    mrb_funcall(mrb, self, m, 0);
  }

  return self;
}

static mrb_value
mrb_gosu_window_is_button_down(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_gosu_window_show(mrb_state *mrb, mrb_value self)
{
  Gosu_Window_show(mrb_gosu_window_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_window_tick(mrb_state *mrb, mrb_value self)
{
  Gosu_Window_tick(mrb_gosu_window_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_window_caption(mrb_state *mrb, mrb_value self)
{
  const char *_caption = Gosu_Window_caption(mrb_gosu_window_get_ptr(mrb, self));

  return mrb_str_new(mrb, _caption, strlen(_caption));
}

static mrb_value
mrb_gosu_window_set_caption(mrb_state *mrb, mrb_value self)
{
  mrb_value caption;
  const int argc = mrb_get_args(mrb, "S", &caption);
  if (argc != 1) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
  }

  Gosu_Window_set_caption(mrb_gosu_window_get_ptr(mrb, self), mrb_string_value_cstr(mrb, &caption));

  return self;
}

static mrb_value
mrb_gosu_window_close_immediately(mrb_state *mrb, mrb_value self)
{
  Gosu_Window_close_immediately(mrb_gosu_window_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_window_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int width, height;
  mrb_float update_interval;
  mrb_bool fullscreen, resizable;
  mrb_gosu_window_data_t *data;

  int const argc = mrb_get_args(mrb, "iibfb", &width, &height, &fullscreen, &update_interval, &resizable);
  if (argc != 5)
  {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
  }

  data = (mrb_gosu_window_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_window_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_window_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_window_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->window = Gosu_Window_create(width, height, fullscreen, update_interval, resizable);

  DATA_PTR(self) = data;

  Gosu_Window_set_update(data->window,       mrb_gosu_window_set_update,       mrb);
  Gosu_Window_set_draw(data->window,         mrb_gosu_window_set_draw,         mrb);
  Gosu_Window_set_button_down(data->window,  mrb_gosu_window_set_button_down,  mrb);
  Gosu_Window_set_button_up(data->window,    mrb_gosu_window_set_button_up,    mrb);
  Gosu_Window_set_drop(data->window,         mrb_gosu_window_set_drop,         mrb);
  Gosu_Window_set_needs_redraw(data->window, mrb_gosu_window_set_needs_redraw, mrb);
  Gosu_Window_set_needs_cursor(data->window, mrb_gosu_window_set_needs_cursor, mrb);
  Gosu_Window_set_close(data->window,        mrb_gosu_window_set_close,        mrb);

  return self;
}

void
mrb_gosu_window_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_window = mrb_define_class_under(mrb, mrb_gosu, "Window", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_window, "initialize", mrb_gosu_window_initialize,        MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_gosu_window, "caption",    mrb_gosu_window_caption,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_window, "caption=",   mrb_gosu_window_set_caption,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_window, "show",       mrb_gosu_window_show,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_window, "tick",       mrb_gosu_window_tick,              MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_window, "close!",     mrb_gosu_window_close_immediately, MRB_ARGS_NONE());
}

void
mrb_gosu_window_free(mrb_state *mrb, mrb_value self)
{

}