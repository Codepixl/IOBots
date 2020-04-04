//
// Created by aaron on 4/3/20.
//

#include <iostream>
#include "KeyboardHardware.h"

KeyboardHardware::KeyboardHardware() {
    keypresses = std::queue<uint16_t>();
};

KeyboardHardware::~KeyboardHardware() = default;

uint8_t KeyboardHardware::getHardwareID() {
    return KEYBOARD_HWID;
}

void KeyboardHardware::interrupt() {
    if(keypresses.size() > 0) {
        attachedBot->B = keypresses.front();
        keypresses.pop();
    } else {
        attachedBot->B = 0;
    }
}

void KeyboardHardware::addKeypress(uint16_t keypress) {
    keypresses.push(keypress);
    while(keypresses.size() > 16) keypresses.pop();
}

bool KeyboardHardware::deserialize(uint8_t *buffer, size_t buffer_size) {
    return true;
}

void KeyboardHardware::serialize(uint8_t *buffer) {
    Hardware::serialize(buffer);
}

size_t KeyboardHardware::calculateSerializedSize() {
    return Hardware::calculateSerializedSize();
}
