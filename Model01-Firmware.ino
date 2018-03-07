// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include "Kaleidoscope.h"

enum { QWERTY, NUMPAD, FUNCTION }; // layers


const PROGMEM kaleidoscope::Key keymaps[][kaleidoscope::hardware::total_keys] = {

  [QWERTY] = KEYMAP_STACKED
  (
      ___,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
      Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T,
      Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G, Key_Tab,
      Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

      Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
      Key_A,


      XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                    Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
      Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
      Key_RightAlt, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

      Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
      Key_B
   ),

};

#if 0
const Key qwerty_keys[] = {
  ___,          Key_1, Key_2, Key_3, Key_4, Key_5, XXX,
  Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T,
  Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G, Key_Tab,
  Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

  Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
  Key_A,


  XXX,          Key_6, Key_7, Key_8,     Key_9,      Key_0,         XXX,
                Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
  Key_Enter,    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
  Key_RightAlt, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

  Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
  Key_B
};
#endif

#if 0
class MyKeyArray {

 public:
  MyKeyArray() {
    for (int i{0}; i < 10; ++i) {
      keys_[i] = Key_A;
      prev_keys_[i] = Key_A;
    }
    keys_[3] = Key_B;
    keys_[7] = Key_B;
  }
  void print() {
    for (int i{0}; i < 10; ++i) {
      delay(100);
      Serial.println(keys_[i].raw, HEX);
    }
  }
 private:
  Key keys_[10];
  Key prev_keys_[10];

  class Iterator;
  friend class MyKeyArray::Iterator;

 public:
  Iterator begin() {
    return Iterator(*this, 0);
  }
  Iterator end() {
    return Iterator(*this, 10);
  }

 private:
  class Iterator {
   public:
    Iterator(MyKeyArray& array, int i) : array_(array), i_(i) {}
    bool operator!=(const Iterator& other) {
      while (i_ < other.i_) {
        if (array_.keys_[i_] != array_.prev_keys_[i_]) {
          return true;
        }
        ++i_;
      }
      return false;
    }
    Key& operator*() { return array_.keys_[i_]; }
    void operator++() { ++i_; }
    // Iterator& operator++() { ++i_; return *this; }
   private:
    MyKeyArray& array_;
    int i_;
  };

};

// // next step: move iterator into MyKeyArray class
// // if that works, make != operator more complex (two arrays, return only the differences)
// class MyIter {
//  public:
//   MyIter(MyKeyArray& array, int i) : array_(array), i_(i) {}
//   bool operator!=(const MyIter& other) { return i_ != other.i_; }
//   Key& operator*() { return array_.keys_[i_]; }
//   MyIter& operator++() { ++i_; return *this; }
//  private:
//   MyKeyArray& array_;
//   int i_;
// };

// MyIter MyKeyArray::begin() {
//   return MyIter(*this, 0);
// }
// MyIter MyKeyArray::end() {
//   return MyIter(*this, 10);
// }
#endif


void setup() {
  // Serial.begin(9600);
  // delay(5000);
  // Serial.println(F("Test begin:"));
  // int array[] = { 1, 2, 3, 4, 5 };
  // for (int i : array) {
  //   delay(100);
  //   Serial.println(i);
  // }
  // for (Key key : qwerty_keys) {
  //   delay(100);
  //   Serial.print(key.raw, HEX);
  //   Serial.print("\n");
  // }
  // MyKeyArray arr;
  // // arr.print();
  // for (Key key : arr) {
  //   delay(100);
  //   Serial.println(key.raw, HEX);
  // }
  // for (Key& key : arr) {
  //   key = Key_B;
  // }
  // for (Key key : arr) {
  //   delay(100);
  //   Serial.println(key.raw, HEX);
  // }
  Kaleidoscope.setup();
}

void loop() {
  Kaleidoscope.loop();
}
