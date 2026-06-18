/**
 * @file HostelManager.h
 * @brief Declaration of HostelService, Accommodation, Reportable, and HostelManager
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Multiple Inheritance, Virtual Inheritance, Diamond Problem, Composition, Abstract Classes, Destructors
 */

#ifndef HOSTELMANAGER_H
#define HOSTELMANAGER_H

#include "HostelBlock.h"
#include "../person/Student.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// ==================== Common Base Class (Diamond Top) ====================
class HostelService {
protected:
    std::string serviceName;

public:
    HostelService(std::string name) : serviceName(name) {
        std::cout << "[HostelService Base Constructor] Created Service: " << serviceName << "\n";
    }

    virtual ~HostelService() {
        std::cout << "[HostelService Base Destructor] Destroyed Service: " << serviceName << "\n";
    }

    virtual void displayService() const {
        std::cout << "Service Name: " << serviceName << "\n";
    }
};

// ==================== Interface 1 (Diamond Left) ====================
class Accommodation : virtual public HostelService {
public:
    Accommodation(std::string name) : HostelService(name) {}
    virtual ~Accommodation() = default;

    virtual void allocateRoom(Room& room, const std::shared_ptr<Student>& student) = 0;
    virtual void vacateRoom(Room& room, const std::shared_ptr<Student>& student) = 0;
};

// ==================== Interface 2 (Diamond Right) ====================
class Reportable : virtual public HostelService {
public:
    Reportable(std::string name) : HostelService(name) {}
    virtual ~Reportable() = default;

    virtual void generateReport() const = 0;
};

// ==================== HostelManager (Diamond Bottom - Multiple Inheritance) ====================
class HostelManager : public Accommodation, public Reportable {
private:
    std::vector<HostelBlock> blocks; // Composition: HostelManager owns HostelBlocks

public:
    // Constructor (Resolves diamond problem by directly invoking virtual base constructor)
    HostelManager(std::string serviceName);

    // Destructor (Fulfills the destructor requirement in checklist)
    virtual ~HostelManager() override;

    // Implementation of Accommodation interface
    virtual void allocateRoom(Room& room, const std::shared_ptr<Student>& student) override;
    virtual void vacateRoom(Room& room, const std::shared_ptr<Student>& student) override;

    // Implementation of Reportable interface
    virtual void generateReport() const override;

    // Block management
    void addBlock(const HostelBlock& block);
    HostelBlock* findBlock(const std::string& name);
    std::vector<HostelBlock>& getBlocks() { return blocks; }
    const std::vector<HostelBlock>& getBlocks() const { return blocks; }
};

#endif // HOSTELMANAGER_H
