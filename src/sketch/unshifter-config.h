// -*- c++ -*-

#pragma once

#include <Kaleidoglyph-Unshifter.h>

namespace kaleidoglyph {
namespace unshifter {

Unkey unkeys[] = {
  {Key_X, KeyboardKey(0x05, 0b0010)},
  {KeyboardKey(0x06, 0b0010), Key_T},
};

byte unkey_count = sizeof(unkeys)/sizeof(unkeys[0]);

} // namespace unshifter {
}
