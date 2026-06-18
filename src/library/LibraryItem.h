/**
 * @file LibraryItem.h
 * @brief Declaration of the Abstract Base Class LibraryItem
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Abstract Classes, Pure Virtual Functions, Encapsulation
 */

#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>

class LibraryItem {
protected:
    std::string itemID;
    std::string title;
    std::string author;
    int publicationYear;

public:
    // Constructor
    LibraryItem(std::string id, std::string t, std::string a, int year)
        : itemID(id), title(t), author(a), publicationYear(year) {}

    // Virtual Destructor
    virtual ~LibraryItem() = default;

    // Pure Virtual Function
    virtual void checkout(const std::string& rollNo) = 0;
    virtual void returnItem() = 0;

    // Getters
    std::string getItemID() const { return itemID; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getPublicationYear() const { return publicationYear; }

    // Setters
    void setItemID(const std::string& id) { itemID = id; }
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const std::string& a) { author = a; }
    void setPublicationYear(int year) { publicationYear = year; }
};

#endif // LIBRARYITEM_H
