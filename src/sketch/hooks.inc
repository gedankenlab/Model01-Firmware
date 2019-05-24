// -*- c++ -*-

// This should really be a *.cpp file, but if it is, the build process will try to compile
// it twice, resulting in confusing "multiple definition" errors at link time (where the
// "multiple definitions" both occur on the same line of the same file). So I call it
// "hooks.inc", and #include it from the sketch file itself. Awkward, but effective.
#pragma once

#include <kaleidoglyph/hooks.h>

#include <Arduino.h>

#include <kaleidoglyph/EventHandlerResult.h>
#include <kaleidoglyph/KeyEvent.h>
#include <kaleidoglyph/hid/keyboard.h>

#include "sketch/KeyEventHandlerId.h"
#include <kaleidoglyph/EventHandlerId.h>
#include <kaleidoglyph/led/LedController.h>


namespace kaleidoglyph {

namespace plugin {
extern macros::Plugin    macros;
extern squeakeys::SqueakeysHandler squeakeys;
}

void toggleHidProtocol() {
  controller.detachFromHost();
  controller.toggleHidProtocol();
  delay(1000);
  controller.attachToHost();
}

namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
void preKeyswitchScan() {
  led_manager.preKeyswitchScan();
  plugin::squeakeys.preKeyswitchScan();
}

void setLedForeground(KeyAddr k) {
  led_manager.setForeground(k);
}

bool setForegroundColor(KeyAddr /*k*/) {
  return false;
}

/// Call keyswitch event handler hooks (run when a key press or release is detected)
/// Order matters here:
EventHandlerResult onKeyswitchEvent(KeyEvent& event) {
  if (event.key == Key{cKeyboardKey::_0}) {
    toggleHidProtocol();
    return EventHandlerResult::abort;
  }

  switch (event.caller) {
    // This looks a bit odd, because the code for each plugin *precedes* its case
    // label. That's because they're ordered, so if Plugin A is the `event.caller`
    // (because Plugin A is the caller), it doesn't get to re-process the event; it goes
    // to Plugin B instead. There are no break statements at the end of each case label
    // intentionally -- this is like an unrolled loop. Plugin A doesn't know which plugin
    // is next in the order (it probably doesn't know anything about what other plugins
    // are included), so it can only call `onKeyswitchEvent()` with itself (or the
    // controller) as `event.caller`.
    case EventHandlerId::controller:
      // no break here; we deliberately fall through to the next plugin
    default:
      return EventHandlerResult::proceed;
  }
}

/// Order doesn't matter here
EventHandlerResult onKeyEvent(byte id, KeyEvent& event) {
  switch (id) {
    case KeyEventHandlerId::macros:
      return plugin::macros.onKeyEvent(event);
    case KeyEventHandlerId::squeakeys:
      return plugin::squeakeys.onKeyEvent(event);
    case KeyEventHandlerId::led_manager:
      return led_manager.onKeyEvent(event);
    default:
      return EventHandlerResult::nxplugin;
  }
}

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
bool preKeyboardReport(hid::keyboard::Report& /*keyboard_report*/) {
  return true;
}

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
void postKeyboardReport(KeyEvent /*event*/) {
}

} // namespace hooks {
} // namespace kaleidoglyph {
