/**
 * @file HostelManager.cpp
 * @brief Implementation of the HostelManager class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Multiple Inheritance, Virtual Inheritance, Diamond Problem, Composition, Destructors
 */

#include "HostelManager.h"

// Constructor resolves Diamond Top constructor parameters
HostelManager::HostelManager(std::string serviceName)
    : HostelService(serviceName), Accommodation(serviceName), Reportable(serviceName) {
    std::cout << "[HostelManager Constructor] Initialized HostelManager Subsystem.\n";
}

HostelManager::~HostelManager() {
    std::cout << "[HostelManager Destructor] Deallocating hostel blocks and closing HostelManager Subsystem.\n";
}

void HostelManager::allocateRoom(Room& room, const std::shared_ptr<Student>& student) {
    if (!student) return;
    
    std::cout << "Attempting to allocate Room " << room.getRoomNumber() 
              << " (" << room.getType() << ") to student " << student->getName() << "...\n";
              
    if (room.isFull()) {
        std::cout << "Error: Room " << room.getRoomNumber() << " is already full!\n";
        return;
    }

    if (room.addOccupant(student)) {
        std::cout << "Success: Allocated Room " << room.getRoomNumber() 
                  << " to student " << student->getName() << "\n";
    } else {
        std::cout << "Error: Could not allocate room (student might already be in this room).\n";
    }
}

void HostelManager::vacateRoom(Room& room, const std::shared_ptr<Student>& student) {
    if (!student) return;

    std::cout << "Attempting to vacate student " << student->getName() 
              << " from Room " << room.getRoomNumber() << "...\n";

    if (room.removeOccupant(student->getRollNo())) {
        std::cout << "Success: Vacated student " << student->getName() 
                  << " from Room " << room.getRoomNumber() << "\n";
    } else {
        std::cout << "Error: Student " << student->getName() 
                  << " was not found in Room " << room.getRoomNumber() << "\n";
    }
}

void HostelManager::generateReport() const {
    std::cout << "\n================ HOSTEL OCCUPANCY REPORT ================\n";
    displayService(); // Call top base class function
    if (blocks.empty()) {
        std::cout << "No hostel blocks available.\n";
    } else {
        for (const auto& block : blocks) {
            std::cout << "Block: " << block.getBlockName() << "\n";
            for (const auto& room : block.getRooms()) {
                std::cout << "  Room " << room.getRoomNumber() 
                          << " | Type: " << room.getType() 
                          << " | Occupants: " << room.getOccupants().size() << "/" << room.getMaxCapacity() 
                          << " | Floor: " << room.getFloor() << "\n";
                if (!room.getOccupants().empty()) {
                    std::cout << "    Occupants List: ";
                    for (const auto& occupant : room.getOccupants()) {
                        std::cout << occupant->getName() << " (" << occupant->getRollNo() << ")  ";
                    }
                    std::cout << "\n";
                }
            }
        }
    }
    std::cout << "=========================================================\n";
}

void HostelManager::addBlock(const HostelBlock& block) {
    blocks.push_back(block);
}

HostelBlock* HostelManager::findBlock(const std::string& name) {
    for (auto& block : blocks) {
        if (block.getBlockName() == name) {
            return &block;
        }
    }
    return nullptr;
}
