// -*- c++ -*-

#pragma once

#include <Kaleidoglyph-Qukeys.h>

namespace kaleidoglyph {
namespace qukeys {

Qukey qukeys[] = {
  {Key_F, Key_LeftShift},
  {Key_D, Key_LeftControl},
  {Key_M, KeyboardKey(0x10, 0b0010)},
};

byte qukey_count = sizeof(qukeys)/sizeof(qukeys[0]);

} // namespace qukeys {
}
