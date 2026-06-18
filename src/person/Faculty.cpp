/**
 * @file Faculty.cpp
 * @brief Implementation of the Faculty class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Constructors, Method Overriding, Polymorphism, Access Specifiers
 */

#include "Faculty.h"
#include <iostream>
#include <algorithm>

Faculty::Faculty(std::string name, std::string cnic, int age, std::string contact,
                 std::string employeeID, std::string department, std::string designation)
    : Person(name, cnic, age, contact), employeeID(employeeID), department(department), designation(designation) {}

void Faculty::displayInfo() const {
    std::cout << "[Faculty Info]\n"
              << "Name: " << name << "\n"
              << "CNIC: " << cnic << "\n"
              << "Age: " << age << "\n"
              << "Contact: " << contact << "\n"
              << "Employee ID: " << employeeID << "\n"
              << "Department: " << department << "\n"
              << "Designation: " << designation << "\n"
              << "Assigned Courses: ";
    if (assignedCourses.empty()) {
        std::cout << "None";
    } else {
        for (const auto& code : assignedCourses) {
            std::cout << code << " ";
        }
    }
    std::cout << "\n----------------------------------------\n";
}

void Faculty::removeCourseCode(const std::string& code) {
    auto it = std::find(assignedCourses.begin(), assignedCourses.end(), code);
    if (it != assignedCourses.end()) {
        assignedCourses.erase(it);
    }
}
