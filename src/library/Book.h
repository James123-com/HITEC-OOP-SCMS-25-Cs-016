/**
 * @file Book.h
 * @brief Declaration of the Book class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Single Inheritance, Encapsulation, Method Overriding
 */

#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"
#include <string>

class Book : public LibraryItem {
private:
    std::string isbn;
    std::string genre;
    int copiesAvailable;

public:
    // Constructor
    Book(std::string id, std::string t, std::string a, int year,
         std::string isbn, std::string gen, int copies);

    // Destructor
    virtual ~Book() = default;

    // Overridden Methods
    virtual void checkout(const std::string& rollNo) override;
    virtual void returnItem() override;

    // Getters and Setters
    std::string getISBN() const { return isbn; }
    std::string getGenre() const { return genre; }
    int getCopiesAvailable() const { return copiesAvailable; }

    void setISBN(const std::string& i) { isbn = i; }
    void setGenre(const std::string& g) { genre = g; }
    void setCopiesAvailable(int c) { copiesAvailable = c; }
};

#endif // BOOK_H
