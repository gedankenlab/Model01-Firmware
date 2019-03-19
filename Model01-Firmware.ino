// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include <Kaleidoglyph.h>

// ================================================================================
// These includes should be added by the pre-build script
#include <Kaleidoglyph-Qukeys.h>
#include <Kaleidoglyph-Unshifter.h>
#include <Kaleidoglyph-Glukeys.h>
// --------------------------------------------------------------------------------
#include <kaleidoglyph/led/SolidColor.h>
#include <kaleidoglyph/led/Breathe.h>
#include <kaleidoglyph/led/Rainbow.h>
#include <kaleidoglyph/cKey/system.h>

// Maybe it's fine to just have a using directive here instead:
// using namespace kaleidoglyph;
namespace kaleidoglyph {


namespace qukeys {

Qukey qukey_defs[] = {
  {Key_F, Key_LeftShift},
  {Key_D, Key_LeftControl},
  {Key_M, KeyboardKey(0x10, 0b0010)}
};

byte qukey_count = arraySize(qukey_defs);

} // namespace qukeys {


namespace unshifter {

const PROGMEM
Unkey unkey_defs[] = {
  {Key_X, KeyboardKey(0x05, 0b0010)},
  {KeyboardKey(0x06, 0b0010), Key_T},
};

byte unkey_count = arraySize(unkey_defs);

} // namespace unshifter {


namespace glukeys{

const PROGMEM
Key glukey_defs[] = {
  Key_LeftShift,
  Key_RightShift,
  LayerKey{1, true},
};

byte glukey_count = arraySize(glukey_defs);

} // namespace qukeys {

// ================================================================================
// Keymap definition
const PROGMEM
Key qwerty_keys[] = KEYMAP_STACKED(
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, cLedKey::next_mode,
    glukeys::GlukeysKey(0), Key_Q, Key_W, Key_E, Key_R, Key_T,
    glukeys::GlukeysKey(1), Key_A, Key_S, qukeys::QukeysKey(1), qukeys::QukeysKey(0), Key_G, Key_Tab,
    glukeys::cGlukey::meta, Key_Z, Key_X, unshifter::UnshifterKey(1), unshifter::UnshifterKey(0), Key_B, glukeys::cGlukey::cancel,

    glukeys::glukeysModifierKey(1), Key_Backspace, Key_LeftGui, glukeys::GlukeysKey(2),
    //Key_LeftControl, Key_Backspace, Key_LeftGui, glukeys::GlukeysKey(2),
    LayerKey(1, 1),


    XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                  Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
    Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    Key_RightAlt, Key_N, qukeys::QukeysKey(2), Key_Comma, Key_Period, Key_Slash,     Key_Minus,

    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    //glukeys::glukeysModifierKey(Key_RightShift), Key_LeftAlt, Key_Spacebar, Key_RightControl,
    LayerKey(1)
);

Layer qwerty {qwerty_keys, arraySize(qwerty_keys)};

const PROGMEM
Key numpad_keys[] = KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, XXX,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, cConsumerKey::VolumeIncrement, cConsumerKey::VolumeDecrement, ___, ___,

    Key_A, Key_A, KeyboardKey(0x04, 0b0010), cSystemKey::Sleep,
    ___,


    XXX, ___, Key_7, Key_8, Key_9, ___, XXX,
         ___, Key_4, Key_5, Key_6, ___, ___,
    ___, ___, Key_1, Key_2, Key_3, ___, ___,
    ___, ___, Key_0, ___,   ___,   ___, ___,

    ___, ___, ___, ___,
    ___
);

Layer numpad {numpad_keys, arraySize(numpad_keys)};

Layer* const layers[] = {
  &qwerty,
  &numpad,
};

Keymap keymap {layers, arraySize(layers)};
// End keymap definition
// --------------------------------------------------------------------------------


// ================================================================================
// keyboard, reporter, controller
hardware::Keyboard keyboard;

Controller controller {keymap, keyboard};
// --------------------------------------------------------------------------------


// ================================================================================
// Plugins
namespace plugin {
qukeys::Plugin    qukeys    {qukeys::qukey_defs, qukeys::qukey_count, keymap, controller};
unshifter::Plugin unshifter {unshifter::unkey_defs, unshifter::unkey_count};
glukeys::Plugin   glukeys   {glukeys::glukey_defs, glukeys::glukey_count, controller};
}

namespace plugin {
glukeys::LedMode glukeys_led_mode{glukeys};
}

LedSolidColorMode dim_blue_background{Color(0, 0, 100)};
LedBreatheMode breathe_mode{170};
LedRainbowMode rainbow_mode;
LedRainbowWaveMode rainbow_wave_mode;

LedBackgroundMode* const led_modes[] = {
  &dim_blue_background,
  &breathe_mode,
  &rainbow_mode,
  &rainbow_wave_mode,
};

LedController led_controller {controller, keyboard, led_modes, arraySize(led_modes)};

} // namespace kaleidoglyph {

#include "sketch/hooks.inc"

inline void reportMeanCycleTime() {
  static uint8_t counter{0};
  static uint32_t start_time = micros();
  if (++counter == 0) {
    uint32_t interval = micros() - start_time;
    uint32_t mean_cycle_time = interval / 256;
    Serial.print(F("mean cycle time: "));
    Serial.print(mean_cycle_time);
    Serial.println(F(" µs"));
    start_time = micros();
  }
}

//#define REPORT_CYCLE_TIME_AVERAGES

#if defined (REPORT_CYCLE_TIME_AVERAGES)
#define SERIAL_DEBUG
#endif

#define SERIAL_DEBUG

void setup() {

#if defined(SERIAL_DEBUG)
  //Serial.begin(115200);
  Serial.begin(9600);
#endif

  kaleidoglyph::controller.init();
  //kaleidoglyph::testLeds();
  kaleidoglyph::led_controller.setActiveMode(3);

}

void loop() {

#if defined(REPORT_CYCLE_TIME_AVERAGES)
  reportMeanCycleTime();
#endif

  kaleidoglyph::controller.run();

  // static uint32_t last_flip_time{0};
  // uint32_t current_time = kaleidoglyph::Controller::scanStartTime();
  // uint32_t elapsed_time = current_time - last_flip_time;
  // if (elapsed_time > 5000) {
  //   kaleidoglyph::led_controller.nextMode();
  //   last_flip_time = current_time;
  // }
}
