/**
 * @file Journal.cpp
 * @brief Implementation of the Journal class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Method Overriding, Encapsulation, Exception Handling
 */

#include "Journal.h"
#include <iostream>
#include <stdexcept>

Journal::Journal(std::string id, std::string t, std::string a, int year,
                 std::string issn, int vol, int issue)
    : LibraryItem(id, t, a, year), issn(issn), volume(vol), issueNumber(issue), checkedOut(false) {}

void Journal::checkout(const std::string& rollNo) {
    if (checkedOut) {
        throw std::runtime_error("Journal '" + title + "' is already checked out!");
    }
    checkedOut = true;
    std::cout << "Journal '" << title << "' (Vol: " << volume << ", Issue: " << issueNumber 
              << ") successfully checked out to " << rollNo << ".\n";
}

void Journal::returnItem() {
    if (!checkedOut) {
        throw std::runtime_error("Journal '" + title + "' was not checked out!");
    }
    checkedOut = false;
    std::cout << "Journal '" << title << "' returned successfully.\n";
}
