#include "mruby.h"
#include <Gosu/Gosu.h>
#include "window.h"

mrb_value
mrb_gosu_milliseconds(mrb_state *mrb) {
  return mrb_fixnum_value(Gosu_milliseconds());
}

mrb_value
mrb_gosu_fps(mrb_state *mrb) {
  return mrb_fixnum_value(Gosu_fps());
}


void mrb_gosu_init(mrb_state *mrb, struct RClass *mrb_gosu) {
  mrb_define_module_function(mrb, mrb_gosu, "fps", mrb_gosu_fps, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_gosu, "milliseconds", mrb_gosu_milliseconds, MRB_ARGS_NONE());
}



void mrb_mruby_gosu_gem_init(mrb_state *mrb) {
struct RClass *mrb_gosu;
mrb_gosu = mrb_define_module(mrb, "Gosu");

  mrb_gosu_init(mrb, mrb_gosu);
  mrb_gosu_window_init(mrb, mrb_gosu);
}

void mrb_mruby_gosu_gem_final(mrb_state *mrb) {
}