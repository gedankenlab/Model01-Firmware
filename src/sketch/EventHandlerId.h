// -*- c++ -*-

#pragma once

#include <Arduino.h>

// Each plugin gets an event handler ID, which is used as the caller parameter
// in the `KeyEvent` object which gets passed to `handleKeyswitchEvent()`. This
// is used especially when re-starting a delayed keyswitch event (e.g. when a
// key is flushed from the Qukeys queue).

namespace kaleidoglyph {

enum class EventHandlerId : byte {
  // `controller` is special, and must always be present, but order is not important (at
  // least for onKeyswitchEvent):
  controller,
  qukeys,
  unshifter,
  glukeys,
  macros,
};

}
