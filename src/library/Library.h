/**
 * @file Library.h
 * @brief Declaration and implementation of the template class Library<T>
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Class Templates, Function Templates, File I/O (fstream), Template Specialization
 */

#ifndef LIBRARY_H
#define LIBRARY_H

#include "LibraryItem.h"
#include "Book.h"
#include "Journal.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

template <typename T>
class Library {
private:
    std::vector<T> items;

public:
    // Constructor
    Library() = default;

    // Destructor
    ~Library() {
        std::cout << "[Library Class Destructor] Cleaned up library catalog resources.\n";
    }

    // Add Item
    void addItem(const T& item) {
        items.push_back(item);
    }

    // Get Items
    const std::vector<T>& getItems() const { return items; }
    std::vector<T>& getItems() { return items; }

    // Template method to search by title
    template <typename ItemType>
    ItemType* searchByTitle(const std::string& title) {
        for (auto& item : items) {
            // Case-insensitive or direct match? Let's do a direct match for title
            if (item.getTitle() == title) {
                return &item;
            }
        }
        return nullptr;
    }

    // Find by ID
    T* findByID(const std::string& id) {
        for (auto& item : items) {
            if (item.getItemID() == id) {
                return &item;
            }
        }
        return nullptr;
    }

    // Save and Load declarations
    void saveToCSV(const std::string& filepath);
    void loadFromCSV(const std::string& filepath);
};

// ==================== Template Specializations for Book ====================

template <>
inline void Library<Book>::saveToCSV(const std::string& filepath) {
    std::ofstream outFile(filepath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << " for writing.\n";
        return;
    }

    // Header
    outFile << "type,itemID,title,author,publicationYear,isbn,genre,copiesAvailable\n";

    for (const auto& book : items) {
        outFile << "Book,"
                << book.getItemID() << ","
                << book.getTitle() << ","
                << book.getAuthor() << ","
                << book.getPublicationYear() << ","
                << book.getISBN() << ","
                << book.getGenre() << ","
                << book.getCopiesAvailable() << "\n";
    }
    outFile.close();
}

template <>
inline void Library<Book>::loadFromCSV(const std::string& filepath) {
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open file " << filepath << " for reading. Starting with empty catalog.\n";
        return;
    }

    items.clear();
    std::string line;
    // Skip header
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, id, title, author, pubYearStr, isbn, genre, copiesStr;

        std::getline(ss, type, ',');
        if (type != "Book") continue;

        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, pubYearStr, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, copiesStr, ',');

        try {
            int year = std::stoi(pubYearStr);
            int copies = std::stoi(copiesStr);
            items.push_back(Book(id, title, author, year, isbn, genre, copies));
        } catch (...) {
            // Ignore malformed rows
        }
    }
    inFile.close();
}

// ==================== Template Specializations for Journal ====================

template <>
inline void Library<Journal>::saveToCSV(const std::string& filepath) {
    std::ofstream outFile(filepath, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << " for writing.\n";
        return;
    }

    // Header
    outFile << "type,itemID,title,author,publicationYear,issn,volume,issueNumber\n";

    for (const auto& journal : items) {
        outFile << "Journal,"
                << journal.getItemID() << ","
                << journal.getTitle() << ","
                << journal.getAuthor() << ","
                << journal.getPublicationYear() << ","
                << journal.getISSN() << ","
                << journal.getVolume() << ","
                << journal.getIssueNumber() << "\n";
    }
    outFile.close();
}

template <>
inline void Library<Journal>::loadFromCSV(const std::string& filepath) {
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open file " << filepath << " for reading. Starting with empty catalog.\n";
        return;
    }

    items.clear();
    std::string line;
    // Skip header
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, id, title, author, pubYearStr, issn, volStr, issueStr;

        std::getline(ss, type, ',');
        if (type != "Journal") continue;

        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, pubYearStr, ',');
        std::getline(ss, issn, ',');
        std::getline(ss, volStr, ',');
        std::getline(ss, issueStr, ',');

        try {
            int year = std::stoi(pubYearStr);
            int vol = std::stoi(volStr);
            int issue = std::stoi(issueStr);
            items.push_back(Journal(id, title, author, year, issn, vol, issue));
        } catch (...) {
            // Ignore malformed rows
        }
    }
    inFile.close();
}

#endif // LIBRARY_H
