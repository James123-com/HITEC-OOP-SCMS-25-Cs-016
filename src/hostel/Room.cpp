/**
 * @file Room.cpp
 * @brief Implementation of the Room class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, STL Containers, Smart Pointers
 */

#include "Room.h"
#include <algorithm>

Room::Room(int number, std::string type, int floor)
    : roomNumber(number), type(type), floor(floor) {}

size_t Room::getMaxCapacity() const {
    if (type == "single") return 1;
    if (type == "double") return 2;
    if (type == "triple") return 3;
    return 0; // Unknown
}

bool Room::isFull() const {
    return occupants.size() >= getMaxCapacity();
}

bool Room::addOccupant(const std::shared_ptr<Student>& student) {
    if (!student || isFull()) return false;
    
    // Check if student is already in room
    for (const auto& occupant : occupants) {
        if (occupant->getRollNo() == student->getRollNo()) return false;
    }

    occupants.push_back(student);
    return true;
}

bool Room::removeOccupant(const std::string& rollNo) {
    auto it = std::remove_if(occupants.begin(), occupants.end(),
        [&rollNo](const std::shared_ptr<Student>& student) {
            return student->getRollNo() == rollNo;
        });
    if (it != occupants.end()) {
        occupants.erase(it, occupants.end());
        return true;
    }
    return false;
}
