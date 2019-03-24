// -*- c++ -*-

namespace kaleidoglyph {
namespace macros {

enum class MacroAction : byte {
  hello,
};

Key handleMacro(byte index) {
  switch (MacroAction(index)) {
    case MacroAction::hello:
      Serial.println(F("Hello, world!"));
      return cKey::clear;
  }
  return cKey::clear;
}

} // namespace macros {
} //