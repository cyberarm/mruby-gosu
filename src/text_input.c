#include "text_input.h"

typedef struct mrb_gosu_text_input_callback
{
  mrb_state *mrb;
  mrb_value self;
} mrb_gosu_text_input_callback;

typedef struct mrb_gosu_text_input_data_t
{
  Gosu_TextInput *text_input;
} mrb_gosu_text_input_data_t;

static void
mrb_gosu_text_input_data_free(mrb_state *mrb, void *ptr)
{
  mrb_gosu_text_input_data_t *data = (mrb_gosu_text_input_data_t *)ptr;

  if (data != NULL)
  {
    if (data->text_input != NULL)
    {
      Gosu_TextInput_destroy(data->text_input);
    }
    mrb_free(mrb, data);
  }
}

static struct mrb_data_type const mrb_gosu_text_input_data_type = {
    "TextInput",
    mrb_gosu_text_input_data_free,
};

Gosu_TextInput *
mrb_gosu_text_input_get_ptr(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_text_input_data_t *data = DATA_PTR(self);
  return data->text_input;
}

static mrb_value
mrb_gosu_text_input_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_gosu_text_input_data_t *data;

  data = (mrb_gosu_text_input_data_t *)DATA_PTR(self);

  if (data)
  {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_gosu_text_input_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_gosu_text_input_data_t *)mrb_malloc(mrb, sizeof(mrb_gosu_text_input_data_t));
  if (data == NULL)
  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "insufficient memory.");
  }
  data->text_input = Gosu_TextInput_create();

  DATA_PTR(self) = data;

  return self;
}

static mrb_value
mrb_gosu_text_input_text(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, Gosu_TextInput_text(mrb_gosu_text_input_get_ptr(mrb, self)));
}

static mrb_value
mrb_gosu_text_input_set_text(mrb_state *mrb, mrb_value self)
{
  mrb_value text;
  mrb_get_args(mrb, "S", &text);

  Gosu_TextInput_set_text(mrb_gosu_text_input_get_ptr(mrb, self), mrb_string_cstr(mrb, text));

  return self;
}

static mrb_value
mrb_gosu_text_input_caret_pos(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Gosu_TextInput_caret_pos(mrb_gosu_text_input_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_text_input_set_caret_pos(mrb_state *mrb, mrb_value self)
{
  mrb_int position;
  mrb_get_args(mrb, "i", &position);

  Gosu_TextInput_set_caret_pos(mrb_gosu_text_input_get_ptr(mrb, self), position);

  return self;
}

static mrb_value
mrb_gosu_text_input_selection_start(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Gosu_TextInput_selection_start(mrb_gosu_text_input_get_ptr(mrb, self)) );
}

static mrb_value
mrb_gosu_text_input_set_selection_start(mrb_state *mrb, mrb_value self)
{
  mrb_int position;
  mrb_get_args(mrb, "i", &position);

  Gosu_TextInput_set_selection_start(mrb_gosu_text_input_get_ptr(mrb, self), position);

  return self;
}

static mrb_value
mrb_gosu_text_input_delete_backward(mrb_state *mrb, mrb_value self)
{
  Gosu_TextInput_delete_backward(mrb_gosu_text_input_get_ptr(mrb, self));

  return self;
}

static mrb_value
mrb_gosu_text_input_delete_forward(mrb_state *mrb, mrb_value self)
{
  Gosu_TextInput_delete_forward(mrb_gosu_text_input_get_ptr(mrb, self));

  return self;
}

void mrb_gosu_text_input_init(mrb_state *mrb, struct RClass *mrb_gosu)
{
  mrb_gosu_text_input = mrb_define_class_under(mrb, mrb_gosu, "TextInput", mrb->object_class);

  mrb_define_method(mrb, mrb_gosu_text_input, "initialize", mrb_gosu_text_input_initialize, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_gosu_text_input, "caret_pos", mrb_gosu_text_input_caret_pos, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_text_input, "caret_pos=", mrb_gosu_text_input_set_caret_pos, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_gosu_text_input, "selection_start", mrb_gosu_text_input_selection_start, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_text_input, "selection_start=", mrb_gosu_text_input_set_selection_start, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_gosu_text_input, "text", mrb_gosu_text_input_text, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_text_input, "text=", mrb_gosu_text_input_set_text, MRB_ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_gosu_text_input, "filter", mrb_gosu_text_input_filter, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_gosu_text_input, "delete_backward", mrb_gosu_text_input_delete_backward, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gosu_text_input, "delete_forward", mrb_gosu_text_input_delete_forward, MRB_ARGS_NONE());
}