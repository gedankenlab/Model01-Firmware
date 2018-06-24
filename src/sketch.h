// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoglyph {

namespace sketch {

constexpr byte plugin_count = 3;

namespace pluginid {
constexpr byte controller = 0;
constexpr byte unshifter  = 1;
constexpr byte qukeys     = 2;
} // namespace id {

} // namespace sketch {

namespace hooks {

EventHandlerResult onKeyswitchEvent(KeyEvent& event) {
  EventHandlerResult result;
  switch (event.caller) {
    case sketch::pluginid::controller:
      result = qukeys::plugin.onKeyEvent(event);
      if (result == EventHandlerResult::abort)
        return result;
    case sketch::pluginid::qukeys:
    default:
      return EventHandlerResult::proceed;
  }
}

EventHandlerResult onKeyEvent(byte plugin_id, KeyEvent& event) {
  switch (plugin_id) {
    case sketch::pluginid::unshifter: return unshifter.onKeyEvent(event);
    default:
      return EventHandlerResult::nxplugin;
  }
}

} // namespace hooks {

} // namespace kaleidoglyph {
