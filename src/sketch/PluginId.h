// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

enum class PluginId : byte {
  // `controller` is special, and must always be present, but order is not important (at
  // least for onKeyswitchEvent):
  controller,
  qukeys,
  unshifter,
};

}
