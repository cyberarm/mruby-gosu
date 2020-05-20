#include "song.h"

struct RClass *mrb_gosu_song;

typedef struct mrb_gosu_song_data_t
{
  Gosu_Song *song;
} mrb_gosu_song_data_t;

static void
mrb_gosu_song_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_song_data_t *data = (mrb_gosu_song_data_t *)ptr;

  if (data != NULL)
  {
    if (data->song != NULL)
    {
      Gosu_Song_destroy(data->song);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_song_data_type = {
    "Song",
    mrb_gosu_song_data_free,
};

Gosu_Song *
mrb_gosu_song_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_song_data_t *data = DATA_PTR(self);
  return data->song;
}

mrb_value
mrb_gosu_song_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_gosu_song_data_t *data;

  mrb_get_args(mrb, "S", &path);

  data = (mrb_gosu_song_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_song_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_song_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_song_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->song = Gosu_Song_create(mrb_string_cstr(mrb, path));

  DATA_PTR(self) = data;

  return self;
}

static mrb_value
mrb_gosu_song_set_volume(mrb_state *mrb, mrb_value self)
{
  mrb_float volume;
  mrb_get_args(mrb, "f", &volume);
  Gosu_Song_set_volume(mrb_gosu_song_get_ptr(mrb, self), volume);

  return self;
}

static mrb_value
mrb_gosu_song_play(mrb_state *mrb, mrb_value self)
{
  mrb_bool looping;
  mrb_get_args(mrb, "b", &looping);
  Gosu_Song_play(mrb_gosu_song_get_ptr(mrb, self), looping);

  return self;
}

static mrb_value
mrb_gosu_song_pause(mrb_state *mrb, mrb_value self)
{
  Gosu_Song_pause(mrb_gosu_song_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_song_is_paused(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value( Gosu_Song_paused(mrb_gosu_song_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_song_is_playing(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value( Gosu_Song_playing(mrb_gosu_song_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_song_stop(mrb_state *mrb, mrb_value self)
{
  Gosu_Song_stop(mrb_gosu_song_get_ptr(mrb, self));

  return self;
}

void mrb_gosu_song_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_song = mrb_define_class_under(mrb, mrb_gosu, "Song", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_song, "initialize", mrb_gosu_song_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_song, "volume=",    mrb_gosu_song_set_volume, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_song, "_play",      mrb_gosu_song_play,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_song, "pause",      mrb_gosu_song_pause,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_song, "paused?",    mrb_gosu_song_is_paused,  MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_song, "playing?",   mrb_gosu_song_is_playing, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_song, "stop",       mrb_gosu_song_stop,       MRB_ARGS_NONE());
}