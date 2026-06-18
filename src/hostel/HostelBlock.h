/**
 * @file HostelBlock.h
 * @brief Declaration of the HostelBlock class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, Composition (Composed inside HostelManager), STL Containers
 */

#ifndef HOSTELBLOCK_H
#define HOSTELBLOCK_H

#include "Room.h"
#include <string>
#include <vector>

class HostelBlock {
private:
    std::string blockName;
    std::vector<Room> rooms;

public:
    // Constructor
    HostelBlock(std::string name);

    // Destructor
    ~HostelBlock() = default;

    // Room management inside block
    void addRoom(const Room& room);
    Room* findRoom(int roomNumber);

    // Getters
    std::string getBlockName() const { return blockName; }
    const std::vector<Room>& getRooms() const { return rooms; }
    std::vector<Room>& getRooms() { return rooms; }
};

#endif // HOSTELBLOCK_H
