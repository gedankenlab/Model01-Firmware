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
      layerKey(1, 1),


      XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                    Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
      Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
      Key_RightAlt, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

      Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
      layerKey(1)
);

Layer qwerty {qwerty_keys, ELEMENTS(qwerty_keys)};

const PROGMEM Key numpad_keys[] = KEYMAP_STACKED(
      ___, ___, ___, ___, ___, ___, XXX,
      ___, ___, ___, ___, ___, ___,
      ___, ___, ___, ___, ___, ___, ___,
      ___, ___, ___, ___, ___, ___, ___,

      ___, ___, ___, ___,
      ___,


      XXX, ___, Key_7, Key_8, Key_9, ___, XXX,
           ___, Key_4, Key_5, Key_6, ___, ___,
      ___, ___, Key_1, Key_2, Key_3, ___, ___,
      ___, ___, Key_0, ___,   ___,   ___, ___,

      ___, ___, ___, ___,
      ___
);

Layer numpad {numpad_keys, ELEMENTS(numpad_keys)};

Layer* layers[] = {
  &qwerty,
  &numpad,
};

Keymap keymap {layers, ELEMENTS(layers)};

hardware::Keyboard keyboard;
hid::keyboard::Report reporter;

Controller controller {keymap, keyboard, reporter};

} // namespace kaleidoscope {


void setup() {
  Serial.begin(9600);
  kaleidoscope::controller.init();
}

void loop() {
  static uint16_t counter{0};
  static uint32_t start_time = micros();
  if (counter == 2048) {
    uint32_t interval = micros() - start_time;
    uint32_t mean_cycle_time = interval / 2048;
    Serial.print(F("average cycle time: "));
    Serial.print(mean_cycle_time);
    Serial.println(F(" µs"));
    counter = 0;
    start_time = micros();
  }

  kaleidoscope::controller.run();

  ++counter;
}
