//
// Created by Aaron on 1/4/18.
//

#ifndef IOBOTS_WORLD_HPP
#define IOBOTS_WORLD_HPP

#include <stdint.h>

/**
 * A struct defining an unsigned x and y position.
 */
struct Position {
    uint16_t x = 0;
    uint16_t y = 0;
};

/**
 * An enum with the four cardinal directions.
 */
enum Heading {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class World {
};

#endif //IOBOTS_WORLD_HPP
