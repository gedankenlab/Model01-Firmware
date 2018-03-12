// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include "Kaleidoscope.h"

// Maybe it's fine to just have a using directive here instead:
// using namespace kaleidoscope;
namespace kaleidoscope {

const PROGMEM Key qwerty_keys[] = KEYMAP_STACKED(
      ___,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
      Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T,
      Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G, Key_Tab,
      Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

      Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
      Key_A,


      XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                    Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
      Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
      Key_RightAlt, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

      Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
      Key_B
);

Layer qwerty {qwerty_keys, ELEMENTS(qwerty_keys)};

Layer* layers[] = {
  &qwerty,
};

Keymap keymap {layers, ELEMENTS(layers)};

hardware::Keyboard keyboard;
hid::keyboard::Report reporter;

Controller controller {keymap, keyboard, reporter};

} // namespace kaleidoscope {


void setup() {
  kaleidoscope::controller.init();
}

void loop() {
  kaleidoscope::controller.run();
}
