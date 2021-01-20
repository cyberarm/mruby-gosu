#pragma once

#include "mruby.h"
#include "mruby/class.h"
#include "Gosu_Color.h"

static struct RClass *mrb_gosu_color;

void mrb_gosu_color_init(mrb_state *mrb, struct RClass *mrb_gosu);