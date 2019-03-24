// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

// I would prefer to use an `enum class` with the `byte` type instead, but C++ won't allow
// conversion from an integer to that type in a switch statement. Even with static_cast,
// it won't compile. I need to use an integer because it's getting incremented in a for
// loop, so my only choice is for these constants to also be that same type (`byte`). That
// should be okay, because this whole file should be generated by the pre-build script(s)
// anyway.
class KeyEventHandlerId {
 public:
  static constexpr byte led_controller = 0;
  static constexpr byte unshifter      = 1;
  static constexpr byte glukeys        = 2;
  static constexpr byte macros         = 3;
  static constexpr byte count          = 4;
};

}
