/**
 * @file Staff.h
 * @brief Declaration of the Staff class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Single Inheritance, Encapsulation, Method Overriding
 */

#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <string>

class Staff : public Person {
private:
    std::string staffID;
    std::string role;
    double salary;

public:
    // Parameterized Constructor
    Staff(std::string name, std::string cnic, int age, std::string contact,
          std::string staffID, std::string role, double salary);

    // Virtual Destructor
    virtual ~Staff() = default;

    // Overridden displayInfo
    virtual void displayInfo() const override;

    // Getters and Setters
    std::string getStaffID() const { return staffID; }
    std::string getRole() const { return role; }
    double getSalary() const { return salary; }

    void setStaffID(const std::string& id) { staffID = id; }
    void setRole(const std::string& r) { role = r; }
    void setSalary(double s) { salary = s; }
};

#endif // STAFF_H
