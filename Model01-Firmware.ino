// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


// The Kaleidoscope core
#include "Kaleidoscope-Core.h"
#include KALEIDOSCOPE_HARDWARE_H


namespace kaleidoscope {

#define TOTAL_KEYS 64 //from KALEIDOSCOPE_HARDWARE_H

// --------------------------------------------------------------------------------
// For mysterious reasons, stringizing requires two levels of indirection
#define __STRINGIZE(A) #A
#define STRINGIZE(A) __STRINGIZE(A)

#define ELEMENTS(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))

// This defines a macro that ensures the right number of keys are defined for a full layer
// (for a PROGMEM layer, obviously)
#define PROGMEM_LAYER(LAYER_NAME, ...)                                           \
  constexpr PROGMEM Key LAYER_NAME ## _keys[] = { __VA_ARGS__ };                 \
  static_assert(ELEMENTS(LAYER_NAME ## _keys) == TOTAL_KEYS,                     \
                "Error: wrong number of keys defined in layer '" #LAYER_NAME "'" \
                "; must be exactly " STRINGIZE(TOTAL_KEYS));                     \
  Layer LAYER_NAME(LAYER_NAME ## _keys);                                         \

// --------------------------------------------------------------------------------

PROGMEM_LAYER(qwerty,
  ___,   ___,   ___,   ___,   ___,   ___,   ___,   ___,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,

  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
);

Layer* layers[] = {
  &qwerty,
};

Keymap keymap{layers, sizeof(layers)/sizeof(layers[0])};

// Hardware
Keyboard keyboard{};

hid::keyboard::Report keyboard_hid_report{};

Main master{keymap, keyboard, keyboard_hid_report};

} // namespace kaleidoscope {

void setup() {
  kaleidoscope::keyboard.init();
  kaleidoscope::keyboard_hid_report.init();
  kaleidoscope::master.init();
}

void loop() {
  kaleidoscope::master.run();
}















constexpr PROGMEM Key base_layer_keys[TOTAL_KEYS] = {
  ___,   ___,   ___,   ___,   ___,   ___,   ___,   ___,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,

  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
  Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H,
};
static_assert(sizeof(base_layer_keys)/sizeof(base_layer_keys[0]) == TOTAL_KEYS,
              "Error: wrong number of keys defined in " #base_layer_keys " -- "
              "Must be exactly " #TOTAL_KEYS);

Layer base_layer(base_layer_keys);

Layer* layers[] = {
  &base_layer,
};

Keymap keymap(layers, sizeof(layers)/sizeof(layers[0]));











enum { QWERTY, NUMPAD, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

//Maybe all these layers need to be declared together?
PROGMEM Layer layer_qwerty = {
  ___, Key_1, Key_2, Key_3,
};

PROGMEM Layer layer_blue = {};

PROGMEM Layer layer_red = {};

// layers[] gets constructed by the pre-build script
PROGMEM Layer layers[] = {
  [0] = (Layer){___, Key_1, Key_2, Key_3, ...},
  [1] = (Layer){___, Key_A, Key_B, Key_C, ...},
  [2] = (Layer){___, Key_X, Key_Y, Key_Z, ...},
  [3] = (Layer){___, Key_7, Key_8, Key_9, ...},
};

// layer_count gets determined by the pre-build script, which also constructs the layers
byte layer_count = 4;

// If the keymap pointer array isn't in progmem, it could be re-ordered
Keymap keymap(layer_count, layers);
// ...but maybe this is better:
Keymap keymap;
for (byte i = 0; i < layer_count; ++i) {
  keymap.add(layers[i]);
}

// Will this work?
Key& operator[](Key table[], KeyAddr k) {
  return table[k.addr()];
}


const Key keymaps[][ROWS][COLS] PROGMEM = {

  [QWERTY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)

};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    &AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumPad,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,

    // The HostPowerManagement plugin enables waking up the host from suspend,
    // and allows us to turn LEDs off when it goes to sleep.
    &HostPowerManagement
  );

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = { 255, 0, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}


// TODO: Test out replacing setup() & loop() with main(). This lets us get rid of (nearly)
// all the ugly global state issues, and enforce dependency declarations. The one minor
// drawback is that it means (I think) the RAM usage will be under-reported in the build,
// but it should be possible to fix that by declaring all local variables in main()
// static. If that doesn't work out, or becomes problematic, it may be possible to
// dispense with either setup() or loop() (but check on serialEventRun() and see if that
// matters at all). Probably easier to use setup(), and add our own infinite loop therein.
int main() {
  // Initialise Arduino functionality.
  init();

  // Attach USB for applicable processors.
#if defined(USBCON)
  USBDevice.attach();
#endif

  setup();  // Call Arduino standard setup function

  while (true) {
    loop(); // Call Arduino standard loop function.

    // Process the serial libaries event queue.
    if (serialEventRun) serialEventRun();
  }
  // Execution should never reach this point.
  return 0x00;
}
