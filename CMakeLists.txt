cmake_minimum_required(VERSION 3.9)
project(IOBots)

set(CMAKE_CXX_STANDARD 17)

add_executable(IOBots main.cpp world/entity/bot/Bot.cpp world/entity/bot/Bot.h world/entity/bot/Assembly.cpp world/entity/bot/Assembly.h world/entity/bot/Assembler.cpp world/entity/bot/Assembler.h Util.cpp Util.h flags.h world/World.cpp world/World.h world/entity/bot/hardware/Hardware.cpp world/entity/bot/hardware/Hardware.h world/entity/bot/hardware/StorageHardware.cpp world/entity/bot/hardware/StorageHardware.h)