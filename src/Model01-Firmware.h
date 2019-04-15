// -*- c++ -*-

#pragma once

// This should come from boards.txt, I think:
//#define KALEIDOGLYPH_HARDWARE_H <Kaleidoglyph-Hardware-Model01.h>

// Type `KeyEventHandlerId`, used by the controller and `onKeyEvent` master hook function:
#define KALEIDOGLYPH_KEY_EVENT_HANDLER_ID_H <sketch/KeyEventHandlerId.h>

// Type `EventHandlerId`, used for handling keyswitch events. Maybe it should be
// `KeyswitchEventHandlerId`, but that name is awfully long, and it's fine to
// assign an ID to each plugin that could be used for other things as well.
#define KALEIDOGLYPH_EVENT_HANDLER_ID_H <sketch/EventHandlerId.h>


#define CONTROLLER_CONSTANTS_H <sketch/controller-constants.h>

//#define QUKEYS_CONSTANTS_H <sketch/qukeys-constants.h>

//#define KALEIDOGLYPH_MACROS_INC <sketch/macros.inc>
