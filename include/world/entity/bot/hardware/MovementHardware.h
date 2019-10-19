//
//  MovementHardware.hpp
//  IOBots
//
//  Created by Aaron on 10/16/19.
//

#ifndef MovementHardware_h
#define MovementHardware_h

#include "Hardware.h"

namespace IOBots::Hardware{
    class MovementHardware: public Hardware {
    private:
    public:
        uint8_t* mem;

        explicit MovementHardware();
        ~MovementHardware();

        uint8_t getHardwareID() override;
        
        /**
         * Movement related functions.
         * A = 0: Move forward.
         * A = 1: Rotate clockwise.
         * A = 2: Rotate counter-clockwise.
         * A = 3: Query position/rotation. Pushes to stack in order of x,y,rotation
         *  Rotation: 0 = north, 1 = east, 2 = south, 3 = west.
        */
        void interrupt() override;
    };

}

#endif /* MovementHardware_hpp */
