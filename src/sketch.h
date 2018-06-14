// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoglyph {

namespace sketch {

constexpr byte plugin_count = 3;

namespace pluginid {
constexpr byte controller = 0;
constexpr byte plugin_a = 1;
constexpr byte plugin_b = 2;
constexpr byte plugin_c = 3;
} // namespace id {

} // namespace sketch {

namespace hooks {

constexpr bool abort   = true;
constexpr bool proceed = false;
bool onKeyEvent(KeyEvent& event) {
  switch (event.caller) {
    case sketch::pluginid::controller:
      if (plugin_a.onKeyEvent(event)) return true;
    case sketch::pluginid::plugin_a:
      if (plugin_b.onKeyEvent(event)) return true;
    case sketch::pluginid::plugin_b:
      if (plugin_c.onKeyEvent(event)) return true;
    case sketch::pluginid::plugin_c:
    default:
      return false;
  }
}

EventHandlerResult onKeyEvent(byte id, KeyEvent& event) {
  switch (id) {
    case sketch::pluginid::plugin_a: return plugin_a.onKeyEvent(event);
    case sketch::pluginid::plugin_b: return plugin_b.onKeyEvent(event);
    case sketch::pluginid::plugin_c: return plugin_c.onKeyEvent(event);
    default:
      return EventHandlerResult::nxplugin;
  }
}

} // namespace hooks {

} // namespace kaleidoglyph {
