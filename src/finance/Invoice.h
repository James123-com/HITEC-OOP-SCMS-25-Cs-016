/**
 * @file Invoice.h
 * @brief Declaration of the Invoice class (Rule of Five & Static Members)
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Static Members, Rule of Five (Move Semantics), Friend Functions, Operator Overloading (<<)
 */

#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include <vector>
#include <iostream>

class Invoice {
private:
    int invoiceID;
    std::string date;
    std::vector<std::string> items;
    double totalAmount;

public:
    // Static Member Variable
    static int invoiceCounter;

    // Static Member Function
    static int getInvoiceCounter() { return invoiceCounter; }

    // Parameterized Constructor
    Invoice(std::string date, std::vector<std::string> items, double totalAmount);

    // Rule of Five: 1. Destructor
    ~Invoice();

    // Rule of Five: 2. Copy Constructor
    Invoice(const Invoice& other);

    // Rule of Five: 3. Copy Assignment Operator
    Invoice& operator=(const Invoice& other);

    // Rule of Five: 4. Move Constructor
    Invoice(Invoice&& other) noexcept;

    // Rule of Five: 5. Move Assignment Operator
    Invoice& operator=(Invoice&& other) noexcept;

    // Friend Function for Stream Insertion
    friend std::ostream& operator<<(std::ostream& os, const Invoice& invoice);

    // Getters
    int getInvoiceID() const { return invoiceID; }
    std::string getDate() const { return date; }
    const std::vector<std::string>& getItems() const { return items; }
    double getTotalAmount() const { return totalAmount; }
};

#endif // INVOICE_H
