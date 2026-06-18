/**
 * @file Enrollment.cpp
 * @brief Implementation of the Enrollment class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, Constructors
 */

#include "Enrollment.h"

Enrollment::Enrollment(std::shared_ptr<Student> student, std::shared_ptr<Course> course,
                       std::string enrollmentDate, std::string grade)
    : student(student), course(course), enrollmentDate(enrollmentDate), grade(grade) {}
