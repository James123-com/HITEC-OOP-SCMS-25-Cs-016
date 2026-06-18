/**
 * @file HostelBlock.cpp
 * @brief Implementation of the HostelBlock class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, Composition, STL Containers
 */

#include "HostelBlock.h"

HostelBlock::HostelBlock(std::string name) : blockName(name) {}

void HostelBlock::addRoom(const Room& room) {
    rooms.push_back(room);
}

Room* HostelBlock::findRoom(int roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            return &room;
        }
    }
    return nullptr;
}
