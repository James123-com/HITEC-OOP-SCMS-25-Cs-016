/**
 * @file Book.cpp
 * @brief Implementation of the Book class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Method Overriding, Encapsulation, Exception Handling
 */

#include "Book.h"
#include <iostream>
#include <stdexcept>

Book::Book(std::string id, std::string t, std::string a, int year,
           std::string isbn, std::string gen, int copies)
    : LibraryItem(id, t, a, year), isbn(isbn), genre(gen), copiesAvailable(copies) {}

void Book::checkout(const std::string& rollNo) {
    if (copiesAvailable <= 0) {
        throw std::runtime_error("Book '" + title + "' is currently out of stock!");
    }
    copiesAvailable--;
    std::cout << "Book '" << title << "' successfully checked out to " << rollNo << ".\n";
}

void Book::returnItem() {
    copiesAvailable++;
    std::cout << "Book '" << title << "' returned successfully. Current copies: " << copiesAvailable << "\n";
}
