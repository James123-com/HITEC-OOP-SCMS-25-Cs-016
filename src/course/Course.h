/**
 * @file Course.h
 * @brief Declaration of the Course class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Encapsulation, Operator Overloading (==, <<, +), Friend Functions, Aggregation
 */

#ifndef COURSE_H
#define COURSE_H

#include "../person/Student.h"
#include "../person/Faculty.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int creditHours;
    std::shared_ptr<Faculty> instructor;                  // Aggregation (Faculty exists independently)
    size_t maxCapacity;
    std::vector<std::shared_ptr<Student>> enrolledStudents;
    std::vector<std::shared_ptr<Student>> waitingList;

public:
    // Constructors
    Course();
    Course(std::string courseCode, std::string courseName, int creditHours,
           std::shared_ptr<Faculty> instructor, size_t maxCapacity);

    // Destructor
    ~Course() = default;

    // Enrollment methods
    void enrollStudent(const std::shared_ptr<Student>& student);
    void addWaitingStudent(const std::shared_ptr<Student>& student);
    void removeStudent(const std::string& rollNo);

    // Operator Overloading
    bool operator==(const Course& other) const;
    std::vector<std::shared_ptr<Student>> operator+(const Course& other) const;

    // Friend function for stream insertion
    friend std::ostream& operator<<(std::ostream& os, const Course& course);

    // Getters and Setters
    std::string getCourseCode() const { return courseCode; }
    std::string getCourseName() const { return courseName; }
    int getCreditHours() const { return creditHours; }
    std::shared_ptr<Faculty> getInstructor() const { return instructor; }
    size_t getMaxCapacity() const { return maxCapacity; }
    const std::vector<std::shared_ptr<Student>>& getEnrolledStudents() const { return enrolledStudents; }
    const std::vector<std::shared_ptr<Student>>& getWaitingList() const { return waitingList; }

    void setCourseCode(const std::string& code) { courseCode = code; }
    void setCourseName(const std::string& name) { courseName = name; }
    void setCreditHours(int hrs) { creditHours = hrs; }
    void setInstructor(const std::shared_ptr<Faculty>& inst) { instructor = inst; }
    void setMaxCapacity(size_t cap) { maxCapacity = cap; }
};

#endif // COURSE_H
