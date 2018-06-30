// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

namespace plugin {
qukeys::Plugin    qukeys    {qukeys::qukey_defs, qukeys::qukey_count, keymap, controller};
unshifter::Plugin unshifter {unshifter::unkeys, unshifter::unkey_count};
}

enum class PluginId : byte {
  controller,
  qukeys,
  unshifter,
};

// Not enum class?
enum class KeyEventHandlerId : byte {
  unshifter,
  // special value `count` must come last; it's used as the upper limit of a for loop
  count,
};

}
