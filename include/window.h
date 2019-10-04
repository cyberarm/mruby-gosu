#pragma once
#include "mruby.h"
#include "stdbool.h"
#include <Gosu/Window.h>

// struct RClass *gosu_window;

Gosu_Window* mrb_gosu_window_create(mrb_state *mrb, int width, int height, bool fullscreen, double update_interval, bool resizable) {
  return Gosu_Window_create(width, height, fullscreen, update_interval, resizable);
}

void mrb_gosu_window_show(mrb_state *mrb, Gosu_Window *window) {
  Gosu_Window_show(window);
}

void mrb_gosu_window_destroy(mrb_state* mrb, Gosu_Window *window) {
  Gosu_Window_destroy(window);
}

void mrb_gosu_window_init(mrb_state *mrb, struct RClass *mrb_gosu);