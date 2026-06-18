/**
 * @file Enrollment.h
 * @brief Declaration of the Enrollment class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, Association (Linking Student and Course)
 */

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../person/Student.h"
#include "Course.h"
#include <string>
#include <memory>

class Enrollment {
private:
    std::shared_ptr<Student> student;
    std::shared_ptr<Course> course;
    std::string enrollmentDate;
    std::string grade;

public:
    // Constructor
    Enrollment(std::shared_ptr<Student> student, std::shared_ptr<Course> course,
               std::string enrollmentDate, std::string grade = "N/A");

    // Destructor
    ~Enrollment() = default;

    // Getters and Setters
    std::shared_ptr<Student> getStudent() const { return student; }
    std::shared_ptr<Course> getCourse() const { return course; }
    std::string getEnrollmentDate() const { return enrollmentDate; }
    std::string getGrade() const { return grade; }

    void setStudent(const std::shared_ptr<Student>& s) { student = s; }
    void setCourse(const std::shared_ptr<Course>& c) { course = c; }
    void setEnrollmentDate(const std::string& date) { enrollmentDate = date; }
    void setGrade(const std::string& g) { grade = g; }
};

#endif // ENROLLMENT_H
