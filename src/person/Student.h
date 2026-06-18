/**
 * @file Student.h
 * @brief Declaration of the Student class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Single Inheritance, Encapsulation, Method Overriding, Polymorphism
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>
#include <string>

class Student : public Person {
protected:
    std::string rollNo;
    int semester;
    double gpa;
    std::vector<std::string> enrolledCourses; // list of course codes

public:
    // Parameterized Constructor
    Student(std::string name, std::string cnic, int age, std::string contact,
            std::string rollNo, int semester, double gpa);
    
    // Virtual Destructor
    virtual ~Student() = default;

    // Overridden displayInfo
    virtual void displayInfo() const override;

    // Custom calculation method
    std::string calculateGrade() const;

    // Getters and Setters
    std::string getRollNo() const { return rollNo; }
    int getSemester() const { return semester; }
    double getGPA() const { return gpa; }
    const std::vector<std::string>& getEnrolledCourses() const { return enrolledCourses; }

    void setRollNo(const std::string& r) { rollNo = r; }
    void setSemester(int sem) { semester = sem; }
    void setGPA(double g) { gpa = g; }
    
    void addCourseCode(const std::string& code) { enrolledCourses.push_back(code); }
    void removeCourseCode(const std::string& code);
};

#endif // STUDENT_H
