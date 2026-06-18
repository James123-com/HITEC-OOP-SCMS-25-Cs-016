/**
 * @file Student.cpp
 * @brief Implementation of the Student class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Constructors, Method Overriding, Polymorphism, Access Specifiers
 */

#include "Student.h"
#include <iostream>
#include <algorithm>

Student::Student(std::string name, std::string cnic, int age, std::string contact,
                 std::string rollNo, int semester, double gpa)
    : Person(name, cnic, age, contact), rollNo(rollNo), semester(semester), gpa(gpa) {}

void Student::displayInfo() const {
    std::cout << "[Student Info]\n"
              << "Name: " << name << "\n"
              << "CNIC: " << cnic << "\n"
              << "Age: " << age << "\n"
              << "Contact: " << contact << "\n"
              << "Roll No: " << rollNo << "\n"
              << "Semester: " << semester << "\n"
              << "GPA: " << gpa << " (Grade: " << calculateGrade() << ")\n"
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

std::string Student::calculateGrade() const {
    if (gpa >= 3.7) return "A";
    if (gpa >= 3.3) return "B+";
    if (gpa >= 3.0) return "B";
    if (gpa >= 2.7) return "B-";
    if (gpa >= 2.3) return "C+";
    if (gpa >= 2.0) return "C";
    if (gpa >= 1.7) return "C-";
    if (gpa >= 1.0) return "D";
    return "F";
}

void Student::removeCourseCode(const std::string& code) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), code);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
    }
}
