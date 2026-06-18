/**
 * @file Invoice.cpp
 * @brief Implementation of the Invoice class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Static Members, Rule of Five, Move Semantics, Friend Functions
 */

#include "Invoice.h"
#include <iostream>

// Initialize static member
int Invoice::invoiceCounter = 1000;

Invoice::Invoice(std::string date, std::vector<std::string> items, double totalAmount)
    : date(date), items(items), totalAmount(totalAmount) {
    invoiceID = ++invoiceCounter;
    std::cout << "[Invoice Constructor] Generated Invoice ID: " << invoiceID << "\n";
}

// Rule of Five: 1. Destructor
Invoice::~Invoice() {
    std::cout << "[Invoice Destructor] Destroyed Invoice ID: " << invoiceID << "\n";
}

// Rule of Five: 2. Copy Constructor
Invoice::Invoice(const Invoice& other)
    : invoiceID(other.invoiceID), date(other.date), items(other.items), totalAmount(other.totalAmount) {
    std::cout << "[Invoice Copy Constructor] Copied Invoice ID: " << invoiceID << "\n";
}

// Rule of Five: 3. Copy Assignment Operator
Invoice& Invoice::operator=(const Invoice& other) {
    std::cout << "[Invoice Copy Assignment Operator] Assigned Invoice ID: " << other.invoiceID << "\n";
    if (this != &other) {
        invoiceID = other.invoiceID;
        date = other.date;
        items = other.items;
        totalAmount = other.totalAmount;
    }
    return *this;
}

// Rule of Five: 4. Move Constructor
Invoice::Invoice(Invoice&& other) noexcept
    : invoiceID(other.invoiceID), date(std::move(other.date)), items(std::move(other.items)), totalAmount(other.totalAmount) {
    other.invoiceID = 0;
    other.totalAmount = 0.0;
    std::cout << "[Invoice Move Constructor] Moved Invoice ID: " << invoiceID << "\n";
}

// Rule of Five: 5. Move Assignment Operator
Invoice& Invoice::operator=(Invoice&& other) noexcept {
    std::cout << "[Invoice Move Assignment Operator] Moved Invoice ID: " << other.invoiceID << "\n";
    if (this != &other) {
        invoiceID = other.invoiceID;
        date = std::move(other.date);
        items = std::move(other.items);
        totalAmount = other.totalAmount;
        
        other.invoiceID = 0;
        other.totalAmount = 0.0;
    }
    return *this;
}

// Friend function for stream insertion
std::ostream& operator<<(std::ostream& os, const Invoice& invoice) {
    os << "---------------- INVOICE #" << invoice.invoiceID << " ----------------\n"
       << "Date: " << invoice.date << "\n"
       << "Items:\n";
    for (const auto& item : invoice.items) {
        os << " - " << item << "\n";
    }
    os << "Total Amount: $" << invoice.totalAmount << "\n"
       << "------------------------------------------------\n";
    return os;
}
