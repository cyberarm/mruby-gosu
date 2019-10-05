#include "window.h"

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
mrb_gosu_window_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int width, height;
  mrb_float update_interval;
  mrb_bool fullscreen, resizable;
  mrb_gosu_window_data_t *data;

  int const argc = mrb_get_args(mrb, "iibfb", &width, &height, &fullscreen, &update_interval, &resizable);
  if (argc != 5) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
  }

  data = (mrb_gosu_window_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_window_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_window_data_t*) mrb_malloc(mrb,  sizeof(mrb_gosu_window_data_t));
  if (data == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->window = Gosu_Window_create(width, height, fullscreen, update_interval, resizable);
  // Gosu_Window_set_update(data->window, &update, mrb);

  DATA_PTR(self)  = data;

  return self;
}

static mrb_value
mrb_gosu_window_show(mrb_state *mrb, mrb_value self)
{
  Gosu_Window_show(mrb_gosu_window_get_ptr(mrb, self));

  return self;
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
mrb_gosu_window_close(mrb_state *mrb, mrb_value self)
{
  return self;
}

void
mrb_gosu_window_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  struct RClass *mrb_gosu_window;
  mrb_gosu_window = mrb_define_class_under(mrb, mrb_gosu, "Window", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_window, "initialize", mrb_gosu_window_initialize,  MRB_ARGS_REQ(5));
  mrb_define_method(mrb, mrb_gosu_window, "caption=",   mrb_gosu_window_set_caption, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_window, "show",       mrb_gosu_window_show,        MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_window, "close",      mrb_gosu_window_close,       MRB_ARGS_NONE());
}

void
mrb_gosu_window_free(mrb_state *mrb, mrb_value self)
{

}