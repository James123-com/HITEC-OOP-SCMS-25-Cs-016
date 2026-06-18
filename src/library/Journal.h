/**
 * @file Journal.h
 * @brief Declaration of the Journal class
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Single Inheritance, Encapsulation, Method Overriding
 */

#ifndef JOURNAL_H
#define JOURNAL_H

#include "LibraryItem.h"
#include <string>

class Journal : public LibraryItem {
private:
    std::string issn;
    int volume;
    int issueNumber;
    bool checkedOut;

public:
    // Constructor
    Journal(std::string id, std::string t, std::string a, int year,
            std::string issn, int vol, int issue);

    // Destructor
    virtual ~Journal() = default;

    // Overridden Methods
    virtual void checkout(const std::string& rollNo) override;
    virtual void returnItem() override;

    // Getters and Setters
    std::string getISSN() const { return issn; }
    int getVolume() const { return volume; }
    int getIssueNumber() const { return issueNumber; }
    bool isCheckedOut() const { return checkedOut; }

    void setISSN(const std::string& i) { issn = i; }
    void setVolume(int v) { volume = v; }
    void setIssueNumber(int num) { issueNumber = num; }
};

#endif // JOURNAL_H
