/**
 * @file Faculty.h
 * @brief Declaration of the Faculty class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Single Inheritance, Encapsulation, Method Overriding
 */

#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include <vector>
#include <string>

class Faculty : public Person {
private:
    std::string employeeID;
    std::string department;
    std::string designation;
    std::vector<std::string> assignedCourses; // list of course codes

public:
    // Parameterized Constructor
    Faculty(std::string name, std::string cnic, int age, std::string contact,
            std::string employeeID, std::string department, std::string designation);

    // Virtual Destructor
    virtual ~Faculty() = default;

    // Overridden displayInfo
    virtual void displayInfo() const override;

    // Getters and Setters
    std::string getEmployeeID() const { return employeeID; }
    std::string getDepartment() const { return department; }
    std::string getDesignation() const { return designation; }
    const std::vector<std::string>& getAssignedCourses() const { return assignedCourses; }

    void setEmployeeID(const std::string& id) { employeeID = id; }
    void setDepartment(const std::string& dept) { department = dept; }
    void setDesignation(const std::string& desg) { designation = desg; }

    void assignCourseCode(const std::string& code) { assignedCourses.push_back(code); }
    void removeCourseCode(const std::string& code);
};

#endif // FACULTY_H
