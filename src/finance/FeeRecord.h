/**
 * @file FeeRecord.h
 * @brief Declaration of the FeeRecord class (Rule of Three)
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Constructors (default, param, copy), Destructors, Copy Semantics (Rule of Three), Operator Overloading
 */

#ifndef FEERECORD_H
#define FEERECORD_H

#include "../person/Student.h"
#include <memory>

class FeeRecord {
private:
    std::shared_ptr<Student> studentRef;
    double semesterFee;
    double hostelFee;
    double libraryFine;
    double totalPaid;
    double balance;

public:
    // Default Constructor
    FeeRecord();

    // Parameterized Constructor
    FeeRecord(std::shared_ptr<Student> student, double semesterFee, double hostelFee, double libraryFine);

    // Rule of Three: 1. Copy Constructor (Deep Copy)
    FeeRecord(const FeeRecord& other);

    // Rule of Three: 2. Copy Assignment Operator
    FeeRecord& operator=(const FeeRecord& other);

    // Rule of Three: 3. Destructor
    ~FeeRecord();

    // Operator Overloading: payment record
    FeeRecord& operator-=(double paymentAmount);

    // Getters and Setters
    std::shared_ptr<Student> getStudentRef() const { return studentRef; }
    double getSemesterFee() const { return semesterFee; }
    double getHostelFee() const { return hostelFee; }
    double getLibraryFine() const { return libraryFine; }
    double getTotalPaid() const { return totalPaid; }
    double getBalance() const { return balance; }

    void setSemesterFee(double fee) { semesterFee = fee; calculateBalance(); }
    void setHostelFee(double fee) { hostelFee = fee; calculateBalance(); }
    void setLibraryFine(double fine) { libraryFine = fine; calculateBalance(); }
    void setStudentRef(const std::shared_ptr<Student>& s) { studentRef = s; }

    void addFine(double amount) { libraryFine += amount; balance += amount; }

private:
    void calculateBalance();
};

#endif // FEERECORD_H
