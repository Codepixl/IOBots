cmake_minimum_required(VERSION 3.9)
project(IOBots)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable(IOBots src/main.cpp src/world/entity/bot/Bot.cpp include/world/entity/bot/Bot.h src/world/entity/bot/Assembly.cpp include/world/entity/bot/Assembly.h src/world/entity/bot/Assembler.cpp include/world/entity/bot/Assembler.h src/Util.cpp include/Util.h include/flags.h src/world/World.cpp include/world/World.h src/world/entity/bot/hardware/Hardware.cpp include/world/entity/bot/hardware/Hardware.h src/world/entity/bot/hardware/StorageHardware.cpp include/world/entity/bot/hardware/StorageHardware.h src/world/entity/bot/hardware/MovementHardware.cpp include/world/entity/bot/hardware/MovementHardware.h)