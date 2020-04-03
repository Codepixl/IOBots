cmake_minimum_required(VERSION 3.7)
project(IOBots)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(src/)
add_executable(IOBots src/main.cpp src/world/bot/Bot.cpp src/world/bot/Bot.hpp src/world/bot/Assembly.cpp src/world/bot/Assembly.hpp src/world/bot/Assembler.cpp src/world/bot/Assembler.hpp src/util/Util.cpp src/util/Util.hpp src/flags.hpp src/world/World.cpp src/world/World.hpp src/world/bot/hardware/Hardware.cpp src/world/bot/hardware/Hardware.hpp src/world/bot/hardware/StorageHardware.cpp src/world/bot/hardware/StorageHardware.hpp src/world/bot/hardware/MovementHardware.cpp src/world/bot/hardware/MovementHardware.hpp src/util/Serializable.cpp src/util/Serializable.hpp src/graphics/Renderer.cpp src/graphics/Renderer.hpp src/IOBots.cpp src/IOBots.hpp)
target_link_libraries(IOBots SDL2::SDL2)