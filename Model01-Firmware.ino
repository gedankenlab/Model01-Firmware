// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include <Kaleidoglyph.h>
#include <kaleidoglyph/utils.h>

// ================================================================================
// These includes should be added by the pre-build script
#include <Kaleidoglyph-Qukeys.h>
#include <Kaleidoglyph-Glukeys.h>
#include <Kaleidoglyph-Unshifter.h>
#include <Kaleidoglyph-Macros.h>
#include <Kaleidoglyph-Squeakeys.h>
// --------------------------------------------------------------------------------
#include <kaleidoglyph/led/SolidColor.h>
#include <kaleidoglyph/led/Breathe.h>
#include <kaleidoglyph/led/Rainbow.h>
#include <kaleidoglyph/cKey/system.h>

#define KK(X) cKeyboardKey::X
#define CK(X) cConsumerKey::X
#define SK(X) cSystemKey::X
#define QK(N) qukeys::QukeysKey(N)
#define GK(N) glukeys::GlukeysKey(N)
#define MK(N) macros::MacrosKey(N)

// Maybe it's fine to just have a using directive here instead:
// using namespace kaleidoglyph;
namespace kaleidoglyph {


namespace qukeys {

const PROGMEM
Qukey qukey_defs[] = {
  {Key_A, Key_LeftGui},
  {Key_S, Key_LeftAlt},
  {Key_D, Key_LeftControl},
  {Key_F, Key_LeftShift},
  {Key_J, Key_RightShift},
  {Key_K, Key_LeftControl},
  {Key_L, Key_LeftAlt},
  {Key_Semicolon, Key_LeftGui},
  {glukeys::cGlukey::cancel, cKey::blank},
  {KK(LeftShift), KK(LeftParen)},
  {KK(RightShift), KK(RightParen)},
  {Key_Spacebar, cKey::blank},

  {Key_M, KeyboardKey(0x10, 0b0010)},
  {Key_E, LayerKey{1, true}},
  {Key_LeftShift, Key_Q},
};

} // namespace qukeys {


namespace unshifter {

const PROGMEM
Unkey unkey_defs[] = {
  {Key_X, KeyboardKey(0x05, 0b0010)},
  {KeyboardKey(0x06, 0b0010), Key_T},
};

} // namespace unshifter {


namespace glukeys {

const PROGMEM
Key glukey_defs[] = {
  LayerKey{1, true},
  Key_LeftShift,
  Key_RightShift,
};

} // namespace glukeys {

enum MacroAction : byte {
  any,
  version,
  hello,
};

// ================================================================================
// Keymap definition
const PROGMEM
Key qwerty_layer_keys[] = KEYMAP_STACKED(
    QK(8),        Key_1, Key_2, Key_3, Key_4, Key_5, cLedKey::next_mode,
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T,
    Key_PageUp,   QK(0), QK(1), QK(2), QK(3), Key_G, Key_Tab,
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

    Key_LeftControl, Key_Backspace, Key_LeftGui, QK(9),
    //glukeys::glukeysModifierKey(1), Key_Backspace, qukeys::QukeysKey(4), glukeys::GlukeysKey(2),
    //Key_LeftControl, Key_Backspace, Key_LeftGui, glukeys::GlukeysKey(2),
    LayerKey(2, true),


    MK(MacroAction::any), Key_6, Key_7, Key_8,     Key_9,      Key_0,     LayerKey(1),
                          Key_Y, Key_U, Key_I,     Key_O,      Key_P,     Key_Equals,
    Key_Enter,            Key_H, QK(4), QK(5),     QK(6),      QK(7),     Key_Quote,
    Key_RightAlt,         Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_Minus,

    QK(10), Key_LeftAlt, Key_Spacebar, Key_RightControl,
    //glukeys::glukeysModifierKey(Key_RightShift), Key_LeftAlt, Key_Spacebar, Key_RightControl,
    LayerKey(2, true)
);

Layer qwerty_layer{qwerty_layer_keys};

const PROGMEM
Key numpad_layer_keys[] = KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,

    ___, ___, ___, ___,
    ___,


    MK(MacroAction::version), ___, Key_7, Key_8,      Key_9,              Key_KeypadSubtract, ___,
                              ___, Key_4, Key_5,      Key_6,              Key_KeypadAdd,      ___,
    ___,                      ___, Key_1, Key_2,      Key_3,              Key_Equals,         ___,
    ___,                      ___, Key_0, Key_Period, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,

    ___, ___, ___, ___,
    ___
);

Layer numpad_layer{numpad_layer_keys};

const PROGMEM
Key function_layer_keys[] = KEYMAP_STACKED(
    QK(11),   Key_F1,          Key_F2,        Key_F3,         Key_F4, Key_F5, Key_CapsLock,
    Key_Tab,  ___,             Key_MouseUp,   ___,            Key_MouseButtonRight,  Key_MouseWarpEnd,
    Key_Home, Key_MouseLeft,   Key_MouseDown, Key_MouseRight, Key_MouseButtonLeft,   Key_MouseWarpNW,  Key_MouseWarpNE,
    Key_End,  Key_PrintScreen, Key_Insert,    ___,            Key_MouseButtonMiddle, Key_MouseWarpSW, Key_MouseWarpSE,

    ___, Key_Delete, ___, ___,
    ___,


    CK(ScanPreviousTrack), Key_F6,             Key_F7,              Key_F8,              Key_F9,          Key_F10,       Key_F11,
                           CK(ScanNextTrack),  KK(LeftCurlyBrace),  KK(RightCurlyBrace), KK(LeftBracket), KK(RightBracket), KK(F12),
    CK(PlaySlashPause),    KK(LeftArrow),      KK(DownArrow),       KK(UpArrow),         KK(RightArrow),  ___,           ___,
    Key_PcApplication,     CK(Mute),           CK(VolumeDecrement), CK(VolumeIncrement), ___,             KK(Backslash), KK(Pipe),

    ___, ___, KK(Enter), ___,
    ___
);

Layer function_layer{function_layer_keys};

PROGMEM
Layer* const layers[] = {
  &qwerty_layer,
  &numpad_layer,
  &function_layer,
};

Keymap keymap{layers};
// End keymap definition
// --------------------------------------------------------------------------------


// ================================================================================
// keyboard, reporter, controller
hardware::Keyboard keyboard;

Controller controller{keymap, keyboard};
// --------------------------------------------------------------------------------


// ================================================================================
// Plugins
namespace plugin {
qukeys::Plugin    qukeys    {qukeys::qukey_defs, keymap, controller};
unshifter::Plugin unshifter {unshifter::unkey_defs};
glukeys::Plugin   glukeys   {glukeys::glukey_defs, controller};
macros::Plugin    macros    {controller};
squeakeys::SqueakeysHandler squeakeys{controller};
}

namespace macros {

void typeVersionInfo(KeyAddr k) {
  plugin::macros.typeProgmemString(PSTR("Keyboardio Model 01 - Kaleidoglyph "), k);
  plugin::macros.typeProgmemString(PSTR("locally built"), k);
}

Key randomKey() {
  byte new_keycode = cKeyboardKey::A.keycode() + byte(Controller::scanStartTime() % 36);
  return KeyboardKey{new_keycode};
}

Key handleMacro(byte index, KeyAddr k) {
  switch (MacroAction(index)) {
    case MacroAction::any:
      return randomKey();
    case MacroAction::version:
      typeVersionInfo(k);
      return cKey::clear;
    case MacroAction::hello:
      plugin::macros.typeProgmemString(PSTR("Hello, world!"), k);
      return cKey::clear;
  }
  return cKey::clear;
}

} // namespace macros {

namespace plugin {
glukeys::LedMode glukeys_led_mode{glukeys};
}

// define LED mode objects
LedSolidColorMode dim_blue_background{Color(0, 0, 100)};
LedBreatheMode breathe_mode{170};
LedRainbowMode rainbow_mode;
LedRainbowWaveMode rainbow_wave_mode;

// calculate the biggest updater footprint
constexpr byte max_updater_size = MaxUpdaterSize<decltype(dim_blue_background),
                                                 decltype(breathe_mode),
                                                 decltype(rainbow_mode),
                                                 decltype(rainbow_wave_mode)>::value;
// allocate memory for the active updater
static byte updater_buffer[max_updater_size] = {};

// create array of updater factories("loaders")
const LedModeLoader pgm_led_mode_loaders[] PROGMEM = {
    {&dim_blue_background,
     loadLedModeUpdater<decltype(dim_blue_background)>},
    {&breathe_mode, loadLedModeUpdater<decltype(breathe_mode)>},
    {&rainbow_mode, loadLedModeUpdater<decltype(rainbow_mode)>},
    {&rainbow_wave_mode, loadLedModeUpdater<decltype(rainbow_wave_mode)>},
};

// create LED manager
LedManager led_manager{pgm_led_mode_loaders, updater_buffer, keyboard};

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

  kaleidoglyph::led_manager.setActiveMode(0);

  kaleidoglyph::plugin::qukeys.setMinimumOverlap(50);
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
