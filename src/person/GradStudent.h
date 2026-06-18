/**
 * @file GradStudent.h
 * @brief Declaration of the GradStudent class (Multi-level Inheritance)
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Multi-level Inheritance (GradStudent : Student : Person), Encapsulation, Method Overriding
 */

#ifndef GRADSTUDENT_H
#define GRADSTUDENT_H

#include "Student.h"
#include <string>

class GradStudent : public Student {
private:
    std::string researchTopic;
    std::string supervisor;

public:
    // Parameterized Constructor
    GradStudent(std::string name, std::string cnic, int age, std::string contact,
                std::string rollNo, int semester, double gpa,
                std::string researchTopic, std::string supervisor);

    // Virtual Destructor
    virtual ~GradStudent() = default;

    // Overridden displayInfo
    virtual void displayInfo() const override;

    // Getters and Setters
    std::string getResearchTopic() const { return researchTopic; }
    std::string getSupervisor() const { return supervisor; }

    void setResearchTopic(const std::string& rt) { researchTopic = rt; }
    void setSupervisor(const std::string& sv) { supervisor = sv; }
};

#endif // GRADSTUDENT_H
