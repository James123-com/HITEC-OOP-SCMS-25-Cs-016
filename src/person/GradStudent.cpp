/**
 * @file GradStudent.cpp
 * @brief Implementation of the GradStudent class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Multi-level Inheritance, Method Overriding, Polymorphism
 */

#include "GradStudent.h"
#include <iostream>

GradStudent::GradStudent(std::string name, std::string cnic, int age, std::string contact,
                         std::string rollNo, int semester, double gpa,
                         std::string researchTopic, std::string supervisor)
    : Student(name, cnic, age, contact, rollNo, semester, gpa),
      researchTopic(researchTopic), supervisor(supervisor) {}

void GradStudent::displayInfo() const {
    std::cout << "[Graduate Student Info]\n"
              << "Name: " << name << "\n"
              << "CNIC: " << cnic << "\n"
              << "Age: " << age << "\n"
              << "Contact: " << contact << "\n"
              << "Roll No: " << rollNo << "\n"
              << "Semester: " << semester << "\n"
              << "GPA: " << gpa << " (Grade: " << calculateGrade() << ")\n"
              << "Research Topic: " << researchTopic << "\n"
              << "Supervisor: " << supervisor << "\n"
              << "Enrolled Courses: ";
    if (enrolledCourses.empty()) {
        std::cout << "None";
    } else {
        for (const auto& code : enrolledCourses) {
            std::cout << code << " ";
        }
    }
    std::cout << "\n----------------------------------------\n";
}
