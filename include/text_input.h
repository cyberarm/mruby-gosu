#pragma once

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/proc.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "stdbool.h"
#include "string.h"
#include "Gosu_TextInput.h"

void mrb_gosu_text_input_init(mrb_state *mrb, struct RClass *mrb_gosu);
Gosu_TextInput *mrb_gosu_text_input_get_ptr(mrb_state *mrb, mrb_value self);