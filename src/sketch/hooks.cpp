// -*- c++ -*-

#pragma once

#include <kaleidoglyph/hooks.h>

#include <Arduino.h>

#include <kaleidoglyph/EventHandlerResult.h>
#include <kaleidoglyph/KeyEvent.h>
#include <kaleidoglyph/hid/Report.h>

#include "sketch/KeyEventHandlerId.h"
#include "sketch/PluginId.h"


namespace kaleidoglyph {

namespace plugin {
extern qukeys::Plugin    qukeys;
extern unshifter::Plugin unshifter;
}

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
    case PluginId::controller:
      result = plugin::qukeys.onKeyEvent(event);
      if (result == EventHandlerResult::abort)
        return result;
    case PluginId::qukeys:
    default:
      return EventHandlerResult::proceed;
  }
}

/// Order doesn't matter here
EventHandlerResult onKeyEvent(KeyEventHandlerId id, KeyEvent& event) {
  switch (id) {
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
