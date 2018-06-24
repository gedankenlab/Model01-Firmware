// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoglyph {
namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
void preKeyswitchScan() {
  plugin::qukeys.preKeyswitchScan();
}

/// Call keyswitch event handler hooks (run when a key press or release is detected)
/// Order matters here:
EventHandlerResult onKeyswitchEvent(KeyEvent& event) {
  EventHandlerResult result;
  switch (event.caller) {
    case pluginid::controller:
      result = plugin::qukeys.onKeyEvent(event);
      if (result == EventHandlerResult::abort)
        return result;
    case pluginid::qukeys:
    default:
      return EventHandlerResult::proceed;
  }
}

/// Order doesn't matter here
EventHandlerResult onKeyEvent(byte plugin_id, KeyEvent& event) {
  switch (plugin_id) {
    case KeyEventHandlerId::unshifter:
      return plugin::unshifter.onKeyEvent(event);
    default:
      return EventHandlerResult::nxplugin;
  }
}

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
bool preKeyboardReport(hid::keyboard::Report& keyboard_report) {
  if (! plugin::unshifter.preKeyboardReport(keyboard_report))
    return false;
  return true;
}

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
void postKeyboardReport(KeyEvent event) {
  plugin::unshifter.postKeyboardReport(event);
}

} // namespace hooks {
} // namespace kaleidoglyph {
