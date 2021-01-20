#pragma once

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/proc.h"
#include "mruby/class.h"
#include "mruby/array.h"
#include "stdbool.h"
#include "string.h"
#include "Gosu.h"

void mrb_gosu_channel_init(mrb_state *mrb, struct RClass *mrb_gosu);