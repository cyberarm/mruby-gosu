#include "channel.h"

struct RClass *mrb_gosu_channel;

typedef struct mrb_gosu_channel_data_t
{
  Gosu_Channel *channel;
} mrb_gosu_channel_data_t;

static void
mrb_gosu_channel_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_channel_data_t *data = (mrb_gosu_channel_data_t *)ptr;

  if (data != NULL)
  {
    if (data->channel != NULL)
    {
      Gosu_Channel_destroy(data->channel);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_channel_data_type = {
    "Channel",
    mrb_gosu_channel_data_free,
};

Gosu_Channel *
mrb_gosu_channel_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_channel_data_t *data = DATA_PTR(self);
  return data->channel;
}

mrb_value
mrb_gosu_channel_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value channel;
  mrb_gosu_channel_data_t *data;

  mrb_get_args(mrb, "o", &channel);

  data = (mrb_gosu_channel_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_channel_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_channel_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_channel_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->channel = Gosu_Channel_create(mrb_cptr(channel));

  DATA_PTR(self) = data;

  return self;
}

static mrb_value
mrb_gosu_channel_set_pan(mrb_state *mrb, mrb_value self)
{
  mrb_float pan;
  mrb_get_args(mrb, "f", &pan);

  Gosu_Channel_set_pan(mrb_gosu_channel_get_ptr(mrb, self), pan);

  return self;
}

static mrb_value
mrb_gosu_channel_set_speed(mrb_state *mrb, mrb_value self)
{
  mrb_float speed;
  mrb_get_args(mrb, "f", &speed);

  Gosu_Channel_set_speed(mrb_gosu_channel_get_ptr(mrb, self), speed);

  return self;
}

static mrb_value
mrb_gosu_channel_set_volume(mrb_state *mrb, mrb_value self)
{
  mrb_float volume;
  mrb_get_args(mrb, "f", &volume);

  Gosu_Channel_set_volume(mrb_gosu_channel_get_ptr(mrb, self), volume);

  return self;
}

static mrb_value
mrb_gosu_channel_pause(mrb_state *mrb, mrb_value self)
{
  Gosu_Channel_pause(mrb_gosu_channel_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_channel_is_paused(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value( Gosu_Channel_paused(mrb_gosu_channel_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_channel_is_playing(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value( Gosu_Channel_playing(mrb_gosu_channel_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_channel_resume(mrb_state *mrb, mrb_value self)
{
  Gosu_Channel_resume(mrb_gosu_channel_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_channel_stop(mrb_state *mrb, mrb_value self)
{
  Gosu_Channel_stop(mrb_gosu_channel_get_ptr(mrb, self));

  return self;
}

void mrb_gosu_channel_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_channel = mrb_define_class_under(mrb, mrb_gosu, "Channel", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_channel, "initialize", mrb_gosu_channel_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_channel, "pan=",       mrb_gosu_channel_set_pan,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_channel, "speed=",     mrb_gosu_channel_set_speed,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_channel, "volume=",    mrb_gosu_channel_set_volume, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_gosu_channel, "pause",      mrb_gosu_channel_pause,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_channel, "paused?",    mrb_gosu_channel_is_paused,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_channel, "playing?",   mrb_gosu_channel_is_playing, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_channel, "resume",     mrb_gosu_channel_resume,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_channel, "stop",       mrb_gosu_channel_stop,       MRB_ARGS_NONE());
}