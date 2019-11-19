//
// Created by Aaron on 11/19/19.
//

#include "util/Serializable.h"

size_t IOBots::Serializable::calculateSerializedSize() {
    return -1;
}

void IOBots::Serializable::serialize(uint8_t *buffer) {

}

bool IOBots::Serializable::deserialize(uint8_t *buffer, size_t buffer_size) {
    return false;
}
