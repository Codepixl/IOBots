//
// Created by aaron on 12/29/2017.
//

#include <iostream>
#include <sstream>
#include "Bot.hpp"
#include "Assembly.hpp"
#include "../../flags.hpp"
#include "../World.hpp"
#include <vector>
#include <cstring>
#include <world/bot/hardware/KeyboardHardware.h>

#include "Assembler.hpp"
#include "hardware/StorageHardware.hpp"
#include "hardware/MovementHardware.hpp"

Bot::Bot(int memSize) {
    mem = new uint8_t[memSize] {0};
    this->memSize = memSize;
    this->SP = static_cast<uint16_t>(memSize - 1);
    this->pos.x = 0;
    this->pos.y = 0;
    addHardware(new StorageHardware(0x10000));
    addHardware(new MovementHardware);
    addHardware(new KeyboardHardware);
}

Bot::Bot(uint8_t *buffer, size_t buffer_size) {
    this->deserialize(buffer, buffer_size);
}

Bot::~Bot() {
    delete mem;
}

void Bot::setMemWord(int loc, uint16_t set) {
    if(loc < memSize) {
        mem[loc] = static_cast<uint8_t>(set & 0xFF);
        mem[loc + 1] = static_cast<uint8_t>((set & 0xFF00) >> 8);
    }
}

uint16_t Bot::getMemWord(int loc) {
    if(loc < memSize)
        return mem[loc] + (static_cast<uint16_t>(mem[loc+1]) << 8);
    return 0x0;
}

int Bot::getMemSize() {
    return memSize;
}

void Bot::step() {
    Instruction instruction {
            mem[PC],
            NUM_OPERANDS[mem[PC]],
            Operand(),
            Operand()
    };

    if(instruction.opcode > sizeof(OPCODES) / sizeof(OPCODES[0])) {
        std::cout << *this << std::endl;
        throw std::runtime_error("Invalid opcode "+std::to_string(instruction.opcode));
    }

    //Pointer to the byte at the end of the instruction
    uint16_t valuePointer = PC + (uint16_t)1;

    //Has at least one operand
    if(instruction.numOperands > 0) {
        instruction.a.type = static_cast<OperandType>(mem[PC + 1] & 0x0F);
        if(instruction.a.hasValue()) {
            valuePointer += 2;
            instruction.a.value = getMemWord(valuePointer-1);
        }
    }
    //Has two operands
    if(instruction.numOperands == 2) {
        instruction.b.type = static_cast<OperandType>((mem[PC+1] & 0xF0) >> 4);
        if(instruction.b.hasValue()) {
            valuePointer += 2;
            instruction.b.value = getMemWord(valuePointer-1);
        }
    }

#if IOBOTS_DEBUG

    std::cout
            << std::hex
            << Assembler::INSTRUCTIONS[instruction.opcode]
            << " " << instruction.a;

    if(instruction.b.type != NONE)
        std::cout << ", " << instruction.b;

    std::cout
            << " @ 0x" << PC
            << std::endl;

#endif

    PC = valuePointer + (uint16_t)1;

    //Execute the instruction
    OPCODES[instruction.opcode](*this, instruction);
}

void Bot::tick() {
    if(!HF)
        step();
}

bool Bot::loadProgram(std::vector<uint8_t> &prog) {
    if(prog.size() > memSize - PROG_OFFSET) return false;
    for(int i = 0; i < prog.size(); i++)
        mem[i+PROG_OFFSET] = prog[i];
    return true;
}

void Bot::interrupt(uint16_t interrupt) {
    //If insead of switch for separate scopes
    if(interrupt == 0x0) { //Print debug info
        std::cout << *this << std::endl;
    } else if(hardwareSlots[interrupt] != nullptr){ //Call a hardware interrupt if it exists
        hardwareSlots[interrupt]->interrupt();
    }
#if IOBOTS_DEBUG
        else
            std::cerr << "nullptr hardware called (0x" << std::hex << A << ")" << std::endl;
#endif
}

uint16_t Bot::move(uint16_t steps) {
    if(steps > energy / ENERGY_MOVE)
        steps = energy / ENERGY_MOVE;
    switch(heading){
        case NORTH:
            pos.y += steps;
            break;
        case EAST:
            pos.x += steps;
            break;
        case SOUTH:
            pos.y -= steps;
            break;
        case WEST:
            pos.x -= steps;
            break;
    }
    energy -= steps * ENERGY_MOVE;
    return steps;
}

bool Bot::addHardware(Hardware* hardware){
    if(hardwareSlots[hardware->getHardwareID()] == nullptr){
        hardwareSlots[hardware->getHardwareID()] = hardware;
        numHardware++;
        hardware->setAttachedBot(this, static_cast<uint8_t>(hardware->getHardwareID()));
        return true;
    }
    return false; //There was already a piece of hardware registered with that interrupt
}

bool Bot::removeHardware(uint8_t slot){
    if(hardwareSlots[slot] != nullptr){
        hardwareSlots[slot]->detach();
        hardwareSlots[slot] = nullptr;
        numHardware--;
        return true;
    }
    return false;
}

Hardware* Bot::getHardware(uint8_t slot) {
    return hardwareSlots[slot];
}

void Bot::push(uint16_t word){
    SP -= 2;
    setMemWord(SP, word);
}

uint16_t Bot::pop(){
    SP += 2;
    return getMemWord(SP - 2);
}

void Bot::serialize(uint8_t *buffer) {
    auto* header = (BOT_HEADER*) buffer;
    header->num_hardware = this->numHardware;
    header->position = this->pos;
    header->heading = this->heading;
    header->energy = this->energy;
    header->A = this->A;
    header->B = this->B;
    header->C = this->C;
    header->D = this->D;
    header->PC = this->PC;
    header->SP = this->SP;
    header->CF = this->CF;
    header->ZF = this->ZF;
    header->SF = this->SF;
    header->OF = this->OF;
    header->HF = this->HF;
    header->mem_size = this->memSize;
    header->body_size = calculateSerializedSize() - sizeof(BOT_HEADER);
    header->magic = BOT_MAGIC;

    buffer += sizeof(BOT_HEADER);
    memcpy(buffer, mem, memSize);
    buffer += memSize;

    for(int i = 0; i < numHardware; i++) {
        this->hardwareSlots[i]->serialize(buffer);
        buffer += this->hardwareSlots[i]->calculateSerializedSize();
    }
}

size_t Bot::calculateSerializedSize() {
    size_t ret = sizeof(BOT_HEADER) + memSize;
    for(int i = 0; i < this->numHardware; i++) {
        ret += this->hardwareSlots[i]->calculateSerializedSize();
    }
    return ret;
}

bool Bot::deserialize(uint8_t* buffer, size_t buffer_size) {
    auto* header = (BOT_HEADER*) buffer;

    if(header->magic != BOT_MAGIC){
        std::cerr << "Bot magic mismatch!" << std::endl;
        return false;
    }
    if(buffer_size - sizeof(BOT_HEADER) != header->body_size) {
        std::cerr << "Bot body size mismatch!" << std::endl;
        return false;
    }

    this->pos = header->position;
    this->energy = header->energy;
    this->heading = header->heading;
    this->A = header->A;
    this->B = header->B;
    this->C = header->C;
    this->D = header->D;
    this->PC = header->PC;
    this->SP = header->SP;
    this->CF = header->CF;
    this->ZF = header->ZF;
    this->SF = header->SF;
    this->OF = header->OF;
    this->HF = header->HF;
    this->memSize = header->mem_size;

    buffer += sizeof(BOT_HEADER);
    this->mem = new uint8_t[this->memSize];
    memcpy(this->mem, buffer, this->memSize);
    buffer += this->memSize;

    for(int i = 0; i < header->num_hardware; i++) {
        auto* hardwareHeader = (HARDWARE_HEADER*) buffer;
        uint32_t hardware_size = hardwareHeader->size;

        addHardware(Hardware::deserializeHardware(buffer, hardware_size));
        buffer += hardware_size;
    }

    return true;
}

void Bot::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 200);
    SDL_Rect rect = {pos.x - 5, pos.y - 5, 10, 10};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    switch(heading) {
        case NORTH:
            SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x, pos.y + 5);
            break;
        case SOUTH:
            SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x, pos.y - 5);
            break;
        case EAST:
            SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + 5, pos.y);
            break;
        case WEST:
            SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x - 5, pos.y);
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Bot& bot){
    return os
            << std::dec
            << "Bot@(" << bot.pos.x << "," << bot.pos.y << "):"
            << "\n\t" << bot.getMemSize() << " bytes mem"
            << "\n\t" << bot.energy << " energy"
            << std::hex
            << "\n\tA  = 0x" << bot.A
            << "\n\tB  = 0x" << bot.B
            << "\n\tC  = 0x" << bot.C
            << "\n\tD  = 0x" << bot.D
            << "\n\tPC = 0x" << bot.PC
            << "\n\tSP = 0x" << bot.SP;
}
