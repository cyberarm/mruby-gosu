if RUBY_ENGINE == "mruby"
  puts "ffi not supported on mruby [2.1.0]"
  raise
end

begin
  require "ffi"
rescue LoadError
  puts "FFI required: gem install ffi"
  raise
end

module GosuC
  LIBRARY_PATH = ["gosu-ffi", File.expand_path("../../gosu/build/ffi/libgosu-ffi.so", File.dirname(__FILE__))]

  extend FFI::Library
  ffi_lib LIBRARY_PATH

  # uint32
  constants = [
    "KB_ESCAPE",
    "KB_F1",
    "KB_F2",
    "KB_F3",
    "KB_F4",
    "KB_F5",
    "KB_F6",
    "KB_F7",
    "KB_F8",
    "KB_F9",
    "KB_F10",
    "KB_F11",
    "KB_F12",
    "KB_0",
    "KB_1",
    "KB_2",
    "KB_3",
    "KB_4",
    "KB_5",
    "KB_6",
    "KB_7",
    "KB_8",
    "KB_9",
    "KB_TAB",
    "KB_RETURN",
    "KB_SPACE",
    "KB_LEFT_SHIFT",
    "KB_RIGHT_SHIFT",
    "KB_LEFT_CONTROL",
    "KB_RIGHT_CONTROL",
    "KB_LEFT_ALT",
    "KB_RIGHT_ALT",
    "KB_LEFT_META",
    "KB_RIGHT_META",
    "KB_BACKSPACE",
    "KB_LEFT",
    "KB_RIGHT",
    "KB_UP",
    "KB_DOWN",
    "KB_HOME",
    "KB_END",
    "KB_INSERT",
    "KB_DELETE",
    "KB_PAGE_UP",
    "KB_PAGE_DOWN",
    "KB_ENTER",
    "KB_BACKTICK",
    "KB_MINUS",
    "KB_EQUALS",
    "KB_LEFT_BRACKET",
    "KB_RIGHT_BRACKET",
    "KB_BACKSLASH",
    "KB_SEMICOLON",
    "KB_APOSTROPHE",
    "KB_COMMA",
    "KB_PERIOD",
    "KB_SLASH",
    "KB_A",
    "KB_B",
    "KB_C",
    "KB_D",
    "KB_E",
    "KB_F",
    "KB_G",
    "KB_H",
    "KB_I",
    "KB_J",
    "KB_K",
    "KB_L",
    "KB_M",
    "KB_N",
    "KB_O",
    "KB_P",
    "KB_Q",
    "KB_R",
    "KB_S",
    "KB_T",
    "KB_U",
    "KB_V",
    "KB_W",
    "KB_X",
    "KB_Y",
    "KB_Z",
    "KB_ISO",
    "KB_NUMPAD_0",
    "KB_NUMPAD_1",
    "KB_NUMPAD_2",
    "KB_NUMPAD_3",
    "KB_NUMPAD_4",
    "KB_NUMPAD_5",
    "KB_NUMPAD_6",
    "KB_NUMPAD_7",
    "KB_NUMPAD_8",
    "KB_NUMPAD_9",
    "KB_NUMPAD_DELETE",
    "KB_NUMPAD_PLUS",
    "KB_NUMPAD_MINUS",
    "KB_NUMPAD_MULTIPLY",
    "KB_NUMPAD_DIVIDE",

    "MS_LEFT",
    "MS_MIDDLE",
    "MS_RIGHT",
    "MS_WHEEL_UP",
    "MS_WHEEL_DOWN",
    "MS_OTHER_0",
    "MS_OTHER_1",
    "MS_OTHER_2",
    "MS_OTHER_3",
    "MS_OTHER_4",
    "MS_OTHER_5",
    "MS_OTHER_6",
    "MS_OTHER_7",

    "GP_LEFT",
    "GP_RIGHT",
    "GP_UP",
    "GP_DOWN",
    "GP_BUTTON_0",
    "GP_BUTTON_1",
    "GP_BUTTON_2",
    "GP_BUTTON_3",
    "GP_BUTTON_4",
    "GP_BUTTON_5",
    "GP_BUTTON_6",
    "GP_BUTTON_7",
    "GP_BUTTON_8",
    "GP_BUTTON_9",
    "GP_BUTTON_10",
    "GP_BUTTON_11",
    "GP_BUTTON_12",
    "GP_BUTTON_13",
    "GP_BUTTON_14",
    "GP_BUTTON_15",

    "GP_0_LEFT",
    "GP_0_RIGHT",
    "GP_0_UP",
    "GP_0_DOWN",
    "GP_0_BUTTON_0",
    "GP_0_BUTTON_1",
    "GP_0_BUTTON_2",
    "GP_0_BUTTON_3",
    "GP_0_BUTTON_4",
    "GP_0_BUTTON_5",
    "GP_0_BUTTON_6",
    "GP_0_BUTTON_7",
    "GP_0_BUTTON_8",
    "GP_0_BUTTON_9",
    "GP_0_BUTTON_10",
    "GP_0_BUTTON_11",
    "GP_0_BUTTON_12",
    "GP_0_BUTTON_13",
    "GP_0_BUTTON_14",
    "GP_0_BUTTON_15",

    "GP_1_LEFT",
    "GP_1_RIGHT",
    "GP_1_UP",
    "GP_1_DOWN",
    "GP_1_BUTTON_0",
    "GP_1_BUTTON_1",
    "GP_1_BUTTON_2",
    "GP_1_BUTTON_3",
    "GP_1_BUTTON_4",
    "GP_1_BUTTON_5",
    "GP_1_BUTTON_6",
    "GP_1_BUTTON_7",
    "GP_1_BUTTON_8",
    "GP_1_BUTTON_9",
    "GP_1_BUTTON_10",
    "GP_1_BUTTON_11",
    "GP_1_BUTTON_12",
    "GP_1_BUTTON_13",
    "GP_1_BUTTON_14",
    "GP_1_BUTTON_15",

    "GP_2_LEFT",
    "GP_2_RIGHT",
    "GP_2_UP",
    "GP_2_DOWN",
    "GP_2_BUTTON_0",
    "GP_2_BUTTON_1",
    "GP_2_BUTTON_2",
    "GP_2_BUTTON_3",
    "GP_2_BUTTON_4",
    "GP_2_BUTTON_5",
    "GP_2_BUTTON_6",
    "GP_2_BUTTON_7",
    "GP_2_BUTTON_8",
    "GP_2_BUTTON_9",
    "GP_2_BUTTON_10",
    "GP_2_BUTTON_11",
    "GP_2_BUTTON_12",
    "GP_2_BUTTON_13",
    "GP_2_BUTTON_14",
    "GP_2_BUTTON_15",

    "GP_3_LEFT",
    "GP_3_RIGHT",
    "GP_3_UP",
    "GP_3_DOWN",
    "GP_3_BUTTON_0",
    "GP_3_BUTTON_1",
    "GP_3_BUTTON_2",
    "GP_3_BUTTON_3",
    "GP_3_BUTTON_4",
    "GP_3_BUTTON_5",
    "GP_3_BUTTON_6",
    "GP_3_BUTTON_7",
    "GP_3_BUTTON_8",
    "GP_3_BUTTON_9",
    "GP_3_BUTTON_10",
    "GP_3_BUTTON_11",
    "GP_3_BUTTON_12",
    "GP_3_BUTTON_13",
    "GP_3_BUTTON_14",
    "GP_3_BUTTON_15",

    "GP_LEFT_STICK_X_AXIS",
    "GP_LEFT_STICK_Y_AXIS",
    "GP_RIGHT_STICK_X_AXIS",
    "GP_RIGHT_STICK_Y_AXIS",
    "GP_LEFT_TRIGGER_AXIS",
    "GP_RIGHT_TRIGGER_AXIS",

    "GP_0_LEFT_STICK_X_AXIS",
    "GP_0_LEFT_STICK_Y_AXIS",
    "GP_0_RIGHT_STICK_X_AXIS",
    "GP_0_RIGHT_STICK_Y_AXIS",
    "GP_0_LEFT_TRIGGER_AXIS",
    "GP_0_RIGHT_TRIGGER_AXIS",

    "GP_1_LEFT_STICK_X_AXIS",
    "GP_1_LEFT_STICK_Y_AXIS",
    "GP_1_RIGHT_STICK_X_AXIS",
    "GP_1_RIGHT_STICK_Y_AXIS",
    "GP_1_LEFT_TRIGGER_AXIS",
    "GP_1_RIGHT_TRIGGER_AXIS",

    "GP_2_LEFT_STICK_X_AXIS",
    "GP_2_LEFT_STICK_Y_AXIS",
    "GP_2_RIGHT_STICK_X_AXIS",
    "GP_2_RIGHT_STICK_Y_AXIS",
    "GP_2_LEFT_TRIGGER_AXIS",
    "GP_2_RIGHT_TRIGGER_AXIS",

    "GP_3_LEFT_STICK_X_AXIS",
    "GP_3_LEFT_STICK_Y_AXIS",
    "GP_3_RIGHT_STICK_X_AXIS",
    "GP_3_RIGHT_STICK_Y_AXIS",
    "GP_3_LEFT_TRIGGER_AXIS",
    "GP_3_RIGHT_TRIGGER_AXIS",



    "BM_DEFAULT",
    "BM_INTERPOLATE",
    "BM_ADD",
    "BM_MULTIPLY",

    "FF_BOLD",
    "FF_ITALIC",
    "FF_UNDERLINE",
    "FF_COMBINATIONS",

    "AL_LEFT",
    "AL_RIGHT",
    "AL_CENTER",
    "AL_JUSTIFY",

    "IF_SMOOTH",
    "IF_TILEABLE_LEFT",
    "IF_TILEABLE_TOP",
    "IF_TILEABLE_RIGHT",
    "IF_TILEABLE_BOTTOM",
    "IF_TILEABLE",
    "IF_RETRO"
  ]

  constants.each do |const|
    attach_variable :"#{const}", :"Gosu_#{const}", :uint32
    GosuC.const_set(const, GosuC.send(:"#{const}"))
  end
end

_constants_ = {}
GosuC.constants.sort.each do |const|
  _constants_[const.to_s] = GosuC.const_get(const)
end

string = ""
string += "module Gosu\n"
_constants_.each do |const, value|
  next if const.to_s == "LIBRARY_PATH"
  string += "  #{const} = #{value}\n"
end
string += "end\n"

path = File.expand_path("../mrblib", __dir__)
File.open("#{path}/constants.rb", "w") do |f|
  f.write string
end
