// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include <Kaleidoglyph.h>
#include <Kaleidoglyph-Qukeys.h>
#include <Kaleidoglyph-Unshifter.h>


// Maybe it's fine to just have a using directive here instead:
// using namespace kaleidoglyph;
namespace kaleidoglyph {


namespace qukeys {

Qukey qukeys[] = {
  {Key_F, Key_LeftShift},
  {Key_D, Key_LeftControl},
  {Key_M, KeyboardKey(0x10, 0b0010)}
};

byte qukey_count = sizeof(qukeys)/sizeof(qukeys[0]);

} // namespace qukeys {


namespace unshifter {

Unkey unkeys[] = {
  {Key_X, KeyboardKey(0x05, 0b0010)},
  {KeyboardKey(0x06, 0b0010), Key_T},
};

byte unkey_count = sizeof(unkeys)/sizeof(unkeys[0]);

} // namespace unshifter {


const PROGMEM Key qwerty_keys[] = KEYMAP_STACKED(
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, KeyboardKey(0x04, 0b0010),
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T,
    Key_PageUp,   Key_A, Key_S, QukeysKey(1), QukeysKey(0), Key_G, Key_Tab,
    Key_PageDown, Key_Z, Key_X, UnshifterKey(1), UnshifterKey(0), Key_B, Key_Escape,

    Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
    LayerKey(1, 1),


    XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                  Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
    Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    Key_RightAlt, Key_N, QukeysKey(2), Key_Comma, Key_Period, Key_Slash,     Key_Minus,

    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    LayerKey(1)
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

namespace qukeys {
Plugin plugin {qukeys, qukey_count, keymap, controller};
}

namespace unshifter {
Plugin plugin {unkeys, unkey_count};
}

Plugin* plugins[] = {
  &qukeys,
  &unshifter,
};

} // namespace kaleidoglyph {

namespace kaleidoglyph {
namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
void preScanHooks() {
  uint16_t current_time = millis();
  qukeys::plugin.preScanHook(current_time);
}

/// Call keyswitch event handler hooks (run when a key press or release is detected)
bool keyswitchEventHooks(KeyswitchEvent& event, KeyArray& active_keys, Plugin*& caller) {

  Key key = event.key;
  byte plugin_count = sizeof(plugins)/sizeof(plugins[0]);
  bool plugin_mask[plugin_count] = {}; // could be a bit field

  byte i{0};
  while (i < plugin_count) {

    // If this plugin has already restarted the event once, skip it:
    if (plugin_mask[i]) {
      ++i;
      continue;
    }

    // Call the plugin's event handler:
    if (! plugins[i]->keyswitchEventHook(event, caller))
      return false;

    // If event.key has changed, previous plugins need a chance to act on the corrected
    // value, so restart the loop:
    if (event.key != key) {
      // Mask the plugin that's causing the restart, to prevent infinite loops:
      plugin_mask[i] = true;
      i = 0;
      key = event.key;
      continue;
    }
    ++i;
  }

  return true;
}

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
bool preKeyboardReportHooks(hid::keyboard::Report& keyboard_report) {
  if (! unshifter::plugin.preReportHook(keyboard_report))
    return false;
  return true;
}

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
void postKeyboardReportHooks(KeyswitchEvent event) {
  unshifter::plugin.postReportHook(event);
}

} // namespace hooks {

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
