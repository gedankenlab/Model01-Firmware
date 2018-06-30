// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

enum class KeyEventHandlerId : byte {
  unshifter,
  // special value `count` must come last; it's used as the upper limit of a for loop
  count,
};

}
