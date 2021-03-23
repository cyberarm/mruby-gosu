typedef struct mrb_gosu_callback_data
{
    mrb_state* mrb;
    mrb_value block;
    mrb_value array;
} mrb_gosu_callback_data;