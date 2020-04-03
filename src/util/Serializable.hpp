//
// Created by Aaron on 11/19/19.
//

#ifndef IOBOTS_SERIALIZABLE_HPP
#define IOBOTS_SERIALIZABLE_HPP

#include <stdio.h>
#include <stdint.h>

class Serializable {
    /**
     * Calculate the size of the serializable, in bytes.
     * @return The size of the serializable, in bytes.
     */
    virtual size_t calculateSerializedSize();

    /**
     * Serialize the serializable into the buffer.
     * @param buffer The buffer to serialize into.
     */
    virtual void serialize(uint8_t* buffer);

    /**
     * Deserialize the serializable.
     * @return If the deserialization was successful.
     */
    virtual bool deserialize(uint8_t* buffer, size_t buffer_size);
};


#endif //IOBOTS_SERIALIZABLE_HPP
