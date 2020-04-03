//
// Created by Aaron on 11/19/19.
//

#include "Serializable.hpp"

size_t Serializable::calculateSerializedSize() {
    return -1;
}

void Serializable::serialize(uint8_t *buffer) {

}

bool Serializable::deserialize(uint8_t *buffer, size_t buffer_size) {
    return false;
}
