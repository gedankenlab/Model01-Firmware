// -*- c++ -*-

#pragma once

// This needs to resolve to some path that is unique; it can't be anything else in the
// build path, which suggests that the sketch should not be located in the `libraries`
// directory with the actual libs. That way, only the sketch that is currently being built
// will be included.
#define KALEIDOGLYPH_PLUGIN_ID_H "sketch/PluginId.h"
