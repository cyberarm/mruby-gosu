#include "sample.h"

typedef struct mrb_gosu_sample_data_t
{
  Gosu_Sample *sample;
} mrb_gosu_sample_data_t;

static void
mrb_gosu_sample_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_sample_data_t *data = (mrb_gosu_sample_data_t *)ptr;

  if (data != NULL)
  {
    if (data->sample != NULL)
    {
      Gosu_Sample_destroy(data->sample);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_sample_data_type = {
    "Sample",
    mrb_gosu_sample_data_free,
};

Gosu_Sample *
mrb_gosu_sample_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_sample_data_t *data = (mrb_gosu_sample_data_t *)DATA_PTR(self);
  return data->sample;
}

mrb_value
mrb_gosu_sample_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_gosu_sample_data_t *data;

  mrb_get_args(mrb, "S", &path);

  data = (mrb_gosu_sample_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_sample_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_sample_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_sample_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->sample = Gosu_Sample_create(mrb_string_cstr(mrb, path));

  DATA_PTR(self) = data;

  return self;
}

static mrb_value
mrb_gosu_sample_play(mrb_state *mrb, mrb_value self)
{
  mrb_float volume, speed;
  mrb_bool looping;

  mrb_get_args(mrb, "ffb", &volume, &speed, &looping);
  Gosu_Channel *pointer = Gosu_Sample_play(
    mrb_gosu_sample_get_ptr(mrb, self), volume, speed, looping);

  mrb_value channel = mrb_cptr_value(mrb, pointer);

  return mrb_obj_new(mrb, mrb_gosu_channel, 1, &channel);
}

static mrb_value
mrb_gosu_sample_play_pan(mrb_state *mrb, mrb_value self)
{
  mrb_float pan, volume, speed;
  mrb_bool looping;

  mrb_get_args(mrb, "fffb", &pan, &volume, &speed, &looping);
  Gosu_Channel *pointer = Gosu_Sample_play_pan(
    mrb_gosu_sample_get_ptr(mrb, self), pan, volume, speed, looping);

  mrb_value channel = mrb_cptr_value(mrb, pointer);

  return mrb_obj_new(mrb, mrb_gosu_channel, 1, &channel);
}

void mrb_gosu_sample_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_sample = mrb_define_class_under(mrb, mrb_gosu, "Sample", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_sample, "initialize", mrb_gosu_sample_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_sample, "_play",      mrb_gosu_sample_play, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_gosu_sample, "_play_pan",  mrb_gosu_sample_play_pan, MRB_ARGS_REQ(4));
}