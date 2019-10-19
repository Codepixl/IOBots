//
// Created by Aaron on 1/4/18.
//

#ifndef IOBOTS_WORLD_H
#define IOBOTS_WORLD_H

namespace IOBots{

	struct Position{
		uint16_t x = 0;
		uint16_t y = 0;
	};

	enum Heading{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};

	class World {
	};

}
#endif //IOBOTS_WORLD_H
