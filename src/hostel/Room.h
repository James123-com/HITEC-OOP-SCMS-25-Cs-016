/**
 * @file Room.h
 * @brief Declaration of the Room class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, STL Containers (vector), Smart Pointers
 */

#ifndef ROOM_H
#define ROOM_H

#include "../person/Student.h"
#include <string>
#include <vector>
#include <memory>

class Room {
private:
    int roomNumber;
    std::string type; // "single", "double", "triple"
    int floor;
    std::vector<std::shared_ptr<Student>> occupants;

public:
    // Constructor
    Room(int number, std::string type, int floor);

    // Destructor
    ~Room() = default;

    // Room operations
    bool isFull() const;
    bool addOccupant(const std::shared_ptr<Student>& student);
    bool removeOccupant(const std::string& rollNo);

    // Getters and Setters
    int getRoomNumber() const { return roomNumber; }
    std::string getType() const { return type; }
    int getFloor() const { return floor; }
    const std::vector<std::shared_ptr<Student>>& getOccupants() const { return occupants; }
    size_t getMaxCapacity() const;
};

#endif // ROOM_H
