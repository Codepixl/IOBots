//
//  MovementHardware.cpp
//  IOBots
//
//  Created by Aaron on 10/16/19.
//

#include "MovementHardware.hpp"
#include "../Bot.hpp"
#include <iostream>

uint8_t MovementHardware::getHardwareID(){
    return MOVEMENT_HWID;
}

MovementHardware::MovementHardware(){
}

MovementHardware::~MovementHardware(){
}

void MovementHardware::interrupt(){
    switch(attachedBot->A) {
        //Move
        case 0:
            attachedBot->move(1);
            break;
        //Rotate CW
        case 1:
            switch(attachedBot->heading) {
                case NORTH:
                    attachedBot->heading = EAST;
                    break;
                case EAST:
                    attachedBot->heading = SOUTH;
                    break;
                case SOUTH:
                    attachedBot->heading = WEST;
                    break;
                case WEST:
                    attachedBot->heading = NORTH;
                    break;
            }
            break;
        //Rotate CCW
        case 2:
            switch(attachedBot->heading) {
                case NORTH:
                    attachedBot->heading = WEST;
                    break;
                case WEST:
                    attachedBot->heading = SOUTH;
                    break;
                case SOUTH:
                    attachedBot->heading = EAST;
                    break;
                case EAST:
                    attachedBot->heading = NORTH;
                    break;
            }
            break;
        //Set rotation
        case 3:
            if(attachedBot->B < 4){
                attachedBot->heading = static_cast<Heading>(attachedBot->B);
            }
            break;
        //Query position & rotation
        case 4:
            attachedBot->push(attachedBot->pos.x);
            attachedBot->push(attachedBot->pos.y);
            switch(attachedBot->heading) {
                case NORTH:
                    attachedBot->push(0);
                    break;
                case EAST:
                    attachedBot->push(1);
                    break;
                case SOUTH:
                    attachedBot->push(2);
                    break;
                case WEST:
                    attachedBot->push(3);
                    break;
            }
            break;

    }
}

bool MovementHardware::deserialize(uint8_t *buffer, size_t buffer_size) {
    return true;
}

void MovementHardware::serialize(uint8_t *buffer) {
    Hardware::serialize(buffer);
}

size_t MovementHardware::calculateSerializedSize() {
    return Hardware::calculateSerializedSize();
}
