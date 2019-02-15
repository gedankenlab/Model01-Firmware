// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

// enum class KeyEventHandlerId : byte {
//   unshifter,
//   // special value `count` must come last; it's used as the upper limit of a for loop
//   count,
// };

// class KeyEventHandlerId {
//  public:
//   static byte count{0};

//   KeyEventHandlerId() : value_(count++) {}

//  private:
//   const byte value_;
// };


class KeyEventHandlerId {
 public:
  static constexpr byte unshifter = 0;
  static constexpr byte count     = 1;
};

// namespace key_event_handler_id {
// constexpr byte unshifter = 0;
// constexpr byte count = 1;
// }

}
