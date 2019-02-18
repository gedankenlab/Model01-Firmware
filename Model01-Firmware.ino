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


// Maybe it's fine to just have a using directive here instead:
// using namespace kaleidoglyph;
namespace kaleidoglyph {


namespace qukeys {

qukeys::Qukey qukey_defs[] = {
  {Key_F, Key_LeftShift},
  {Key_D, Key_LeftControl},
  {Key_M, KeyboardKey(0x10, 0b0010)}
};

byte qukey_count = ELEMENTS(qukey_defs);

} // namespace qukeys {


namespace unshifter {

unshifter::Unkey unkeys[] = {
  {Key_X, KeyboardKey(0x05, 0b0010)},
  {KeyboardKey(0x06, 0b0010), Key_T},
};

byte unkey_count = ELEMENTS(unkeys);

} // namespace unshifter {


namespace glukeys{

Key glukey_defs[] = {
  Key_LeftShift,
  Key_RightShift,
  Key_C,
};

byte glukey_count = ELEMENTS(glukey_defs);

} // namespace qukeys {

// ================================================================================
// Keymap definition
const PROGMEM
Key qwerty_keys[] = KEYMAP_STACKED(
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, KeyboardKey(0x04, 0b0010),
    glukeys::GlukeysKey(0), Key_Q, Key_W, Key_E, Key_R, Key_T,
    glukeys::GlukeysKey(1), Key_A, Key_S, qukeys::QukeysKey(1), qukeys::QukeysKey(0), Key_G, Key_Tab,
    glukeys::GlukeysKey(3), Key_Z, Key_X, unshifter::UnshifterKey(1), unshifter::UnshifterKey(0), Key_B, Key_Escape,

    Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
    LayerKey(1, 1),


    XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                  Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
    Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    Key_RightAlt, Key_N, qukeys::QukeysKey(2), Key_Comma, Key_Period, Key_Slash,     Key_Minus,

    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    LayerKey(1)
);

Layer qwerty {qwerty_keys, ELEMENTS(qwerty_keys)};

const PROGMEM
Key numpad_keys[] = KEYMAP_STACKED(
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
// End keymap definition
// --------------------------------------------------------------------------------


// ================================================================================
// keyboard, reporter, controller
hardware::Keyboard keyboard;
hid::keyboard::Report reporter;

Controller controller {keymap, keyboard, reporter};
// --------------------------------------------------------------------------------


// ================================================================================
// Plugins
namespace plugin {
qukeys::Plugin    qukeys    {qukeys::qukey_defs, qukeys::qukey_count, keymap, controller};
unshifter::Plugin unshifter {unshifter::unkeys, unshifter::unkey_count};
glukeys::Plugin   glukeys   {glukeys::glukey_defs, glukeys::glukey_count, controller};
}

// // maybe enum instead?
// namespace pluginid {
// constexpr byte controller {0};
// constexpr byte qukeys     {1};
// constexpr byte unshifter  {2};
// }
// // order doesn't matter here:
// enum class PluginId : byte {
//   controller,
//   qukeys,
//   unshifter,
// };

// // also maybe enum -- order matters here:
// namespace KeyEventHandlerId {
// constexpr byte unshifter {0};
// }

// // order matters here
// enum class KeyEventHandlerId : byte {
//   unshifter = 0,
// };

} // namespace kaleidoglyph {

#include "sketch/hooks.inc"
namespace kaleidoglyph {
// namespace hooks {

// /// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
// void preKeyswitchScan() {
//   plugin::qukeys.preKeyswitchScan();
// }

// /// Call keyswitch event handler hooks (run when a key press or release is detected)
// /// Order matters here:
// EventHandlerResult onKeyswitchEvent(KeyEvent& event) {
//   EventHandlerResult result;
//   switch (event.caller) {
//     case pluginid::controller:
//       result = plugin::qukeys.onKeyswitchEvent(event);
//       if (result == EventHandlerResult::abort)
//         return result;
//     case pluginid::qukeys:
//     default:
//       return EventHandlerResult::proceed;
//   }
// }

// /// Order doesn't matter here
// EventHandlerResult onKeyEvent(byte plugin_id, KeyEvent& event) {
//   switch (plugin_id) {
//     case KeyEventHandlerId::unshifter:
//       return plugin::unshifter.onKeyEvent(event);
//     default:
//       return EventHandlerResult::nxplugin;
//   }
// }

// /// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
// bool preKeyboardReport(hid::keyboard::Report& keyboard_report) {
//   if (! plugin::unshifter.preKeyboardReport(keyboard_report))
//     return false;
//   return true;
// }

// /// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
// void postKeyboardReport(KeyEvent event) {
//   plugin::unshifter.postKeyboardReport(event);
// }

// } // namespace hooks {

void testLeds() {
  // for (byte i{0}; i < 64; ++i) {
  //   LedAddr l{i};
  //   keyboard.setLedColor(l, {255, 0, 0});
  //   delay(100);
  //   // keyboard.updateLeds();
  //   // delay(100);
  //   keyboard.setLedColor(l, {0,0,0});
  //   // keyboard.updateLeds();
  //   delay(100);
  //   // keyboard.setLedColor(l, {0,0,0});
  //   // delay(10);
  // }
  delay(5000);
  keyboard.testLeds();
  delay(1000);
  // keyboard.setAllLeds({200,250,0});
  // for (LedAddr l{0}; l < LedAddr{64}; ++l) {
  //   keyboard.setLedColor(l, {0, 200, 226});
  //   keyboard.updateLeds();
  //   delay(100);
  //   // keyboard.setLedColor(l, {0,0,0});
  //   // // keyboard.updateLeds();
  //   // delay(10);
  // }
  // // for (byte i{0}; i < 64; ++i) {
  // //   LedAddr l{i};
  // //   delay(100);
  // //   keyboard.setLedColor(l, {0,0,0});
  // // }
  // // for (LedAddr l{0}; l < LedAddr{64}; ++l) {
  // //   delay(100);
  // //   keyboard.setLedColor(l, {0,0,0});
  // // }
  // for (KeyAddr k{cKeyAddr::start}; k < cKeyAddr::end; ++k) {
  //   // uint32_t foo = micros();
  //   // byte r = foo & 0xFF; foo >>= 4;
  //   // byte g = foo & 0xFF; foo >>= 4;
  //   // byte b = foo & 0xFF;
  //   // Color color(r, g, b);
  //   keyboard.setKeyColor(k, {200,100,0});
  //   keyboard.updateLeds();
  //   delay(500);
  //   keyboard.setKeyColor(k, {0,0,0});
  //   // keyboard.updateLeds();
  //   delay(50);
  // }
}

} // namespace kaleidoglyph {


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
  Serial.begin(9600);
#endif

  kaleidoglyph::controller.init();
  // kaleidoglyph::testLeds();
}

void loop() {

#if defined(REPORT_CYCLE_TIME_AVERAGES)
  reportMeanCycleTime();
#endif

  kaleidoglyph::controller.run();
}
