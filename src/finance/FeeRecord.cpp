/**
 * @file FeeRecord.cpp
 * @brief Implementation of the FeeRecord class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Copy Semantics (Rule of Three), Deep Copy, Operator Overloading, Constructors
 */

#include "FeeRecord.h"
#include <iostream>

FeeRecord::FeeRecord() 
    : studentRef(nullptr), semesterFee(0.0), hostelFee(0.0), libraryFine(0.0), totalPaid(0.0), balance(0.0) {}

FeeRecord::FeeRecord(std::shared_ptr<Student> student, double semesterFee, double hostelFee, double libraryFine)
    : studentRef(student), semesterFee(semesterFee), hostelFee(hostelFee), libraryFine(libraryFine), totalPaid(0.0) {
    calculateBalance();
}

// Rule of Three: Copy Constructor (Deep Copy)
FeeRecord::FeeRecord(const FeeRecord& other) {
    if (other.studentRef) {
        // Creates a deep copy of the Student object inside a new shared_ptr
        this->studentRef = std::make_shared<Student>(*other.studentRef);
    } else {
        this->studentRef = nullptr;
    }
    this->semesterFee = other.semesterFee;
    this->hostelFee = other.hostelFee;
    this->libraryFine = other.libraryFine;
    this->totalPaid = other.totalPaid;
    this->balance = other.balance;
    std::cout << "[FeeRecord Copy Constructor] Performed Deep Copy of Student " 
              << (this->studentRef ? this->studentRef->getName() : "Unknown") << "\n";
}

// Rule of Three: Copy Assignment Operator
FeeRecord& FeeRecord::operator=(const FeeRecord& other) {
    std::cout << "[FeeRecord Copy Assignment Operator] Called.\n";
    if (this != &other) {
        if (other.studentRef) {
            // Creates a deep copy of the Student object
            this->studentRef = std::make_shared<Student>(*other.studentRef);
        } else {
            this->studentRef = nullptr;
        }
        this->semesterFee = other.semesterFee;
        this->hostelFee = other.hostelFee;
        this->libraryFine = other.libraryFine;
        this->totalPaid = other.totalPaid;
        this->balance = other.balance;
    }
    return *this;
}

// Rule of Three: Destructor
FeeRecord::~FeeRecord() {
    std::cout << "[FeeRecord Destructor] Destroyed FeeRecord for Roll No: " 
              << (studentRef ? studentRef->getRollNo() : "N/A") << "\n";
}

FeeRecord& FeeRecord::operator-=(double paymentAmount) {
    if (paymentAmount <= 0.0) return *this;
    
    totalPaid += paymentAmount;
    balance -= paymentAmount;
    std::cout << "Recorded payment of $" << paymentAmount << " for student " 
              << (studentRef ? studentRef->getRollNo() : "N/A") 
              << ". Remaining Balance: $" << balance << "\n";
    return *this;
}

void FeeRecord::calculateBalance() {
    balance = (semesterFee + hostelFee + libraryFine) - totalPaid;
}
