//
// Created by aaron on 4/3/20.
//

#ifndef IOBOTS_KEYBOARDHARDWARE_H
#define IOBOTS_KEYBOARDHARDWARE_H


#include <queue>
#include "Hardware.hpp"

class KeyboardHardware: public Hardware {
private:
    std::queue<uint16_t> keypresses;
public:
    explicit KeyboardHardware();
    ~KeyboardHardware();

    uint8_t getHardwareID() override;

    /**
     * Gets the next keyboard keypress in the buffer and puts it into the B register.
     * Will be zero if there are no keypresses in the buffer.
     */
    void interrupt() override;

    /**
     * Adds a keypress to the queue.
     */
    void addKeypress(uint16_t keypress);

    bool deserialize(uint8_t* buffer, size_t buffer_size) override;
    void serialize(uint8_t* buffer) override;
    size_t calculateSerializedSize() override;
};


#endif //IOBOTS_KEYBOARDHARDWARE_H
