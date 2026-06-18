/**
 * @file Staff.cpp
 * @brief Implementation of the Staff class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Constructors, Method Overriding, Polymorphism, Access Specifiers
 */

#include "Staff.h"
#include <iostream>

Staff::Staff(std::string name, std::string cnic, int age, std::string contact,
             std::string staffID, std::string role, double salary)
    : Person(name, cnic, age, contact), staffID(staffID), role(role), salary(salary) {}

void Staff::displayInfo() const {
    std::cout << "[Staff Info]\n"
              << "Name: " << name << "\n"
              << "CNIC: " << cnic << "\n"
              << "Age: " << age << "\n"
              << "Contact: " << contact << "\n"
              << "Staff ID: " << staffID << "\n"
              << "Role: " << role << "\n"
              << "Salary: $" << salary << "\n"
              << "----------------------------------------\n";
}
