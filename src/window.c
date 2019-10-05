#include "window.h"

typedef struct mrb_gosu_window_data_t {
  Gosu_Window *window;
} mrb_gosu_window_data_t;

static void mrb_gosu_window_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_window_data_t *data = (mrb_gosu_window_data_t*)ptr;

  if (data != NULL) {
    if (data->window != NULL) {
      Gosu_Window_destroy(data->window);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_window_data_type = {
  "Window", mrb_gosu_window_data_free
};

Gosu_Window *mrb_gosu_window_get_ptr(mrb_state *mrb, mrb_value window)
{
  mrb_gosu_window_data_t *data;
  if (mrb_nil_p(window)) {
    return NULL;
  }
  data = (mrb_gosu_window_data_t*)mrb_data_get_ptr(mrb, window, &mrb_gosu_window_data_type);
  return data->window;
}

static mrb_value mrb_gosu_window_initialize(mrb_state *mrb, mrb_value self) {
  mrb_int width, height;
  mrb_float update_interval;
  mrb_bool fullscreen, resizable;

  int const argc = mrb_get_args(mrb, "iibdb", &width, &height, &fullscreen, &update_interval, &resizable);
  if (5 != argc) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments.");
  }

  mrb_gosu_window_data_t* data = (mrb_gosu_window_data_t*) DATA_PTR(self);
  data = (mrb_gosu_window_data_t*) mrb_malloc(mrb,  sizeof(mrb_gosu_window_data_t));
  if (data == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->window = Gosu_Window_create(width, height, fullscreen, update_interval, resizable);

  DATA_PTR(self)  = data;
  DATA_TYPE(self) = &mrb_gosu_window_data_type;

  return self;
}

mrb_value mrb_gosu_window_show(mrb_state *mrb, mrb_value window) {
}
mrb_value mrb_gosu_window_close(mrb_state *mrb, mrb_value window) {
}

void mrb_gosu_window_init(mrb_state *mrb, struct RClass *mrb_gosu) {
  struct RClass *mrb_gosu_window;
  mrb_gosu_window = mrb_define_class(mrb, "Window", mrb_gosu);

  mrb_define_class_method(mrb, mrb_gosu_window, "initialize", mrb_gosu_window_initialize, MRB_ARGS_REQ(5));
  mrb_define_class_method(mrb, mrb_gosu_window, "show",       mrb_gosu_window_show,       MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_gosu_window, "close",      mrb_gosu_window_close,      MRB_ARGS_NONE());
}

void mrb_gosu_window_free(mrb_state *mrb, mrb_value self) {

}