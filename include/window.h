#pragma once

#include "mruby.h"
#include "mruby/data.h"
#include "stdbool.h"
#include <Gosu/Window.h>

// struct RClass *gosu_window;

static mrb_value mrb_gosu_window_initialize(mrb_state *mrb, mrb_value self);
mrb_value mrb_gosu_window_show(mrb_state *mrb, mrb_value self);
mrb_value mrb_gosu_window_close(mrb_state *mrb, mrb_value self);
mrb_value mrb_gosu_window_destroy(mrb_state* mrb, mrb_value self);

void mrb_gosu_window_init(mrb_state *mrb, struct RClass *mrb_gosu);