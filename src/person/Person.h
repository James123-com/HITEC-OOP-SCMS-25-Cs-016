/**
 * @file Person.h
 * @brief Declaration of the Abstract Base Class Person
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Abstract Classes, Pure Virtual Functions, Encapsulation
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    std::string cnic;
    int age;
    std::string contact;

public:
    // Constructor
    Person(std::string name, std::string cnic, int age, std::string contact);
    
    // Virtual Destructor
    virtual ~Person() = default;
    
    // Pure Virtual Function
    virtual void displayInfo() const = 0;
    
    // Getters
    std::string getName() const { return name; }
    std::string getCNIC() const { return cnic; }
    int getAge() const { return age; }
    std::string getContact() const { return contact; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setCNIC(const std::string& newCNIC) { cnic = newCNIC; }
    void setAge(int newAge) { age = newAge; }
    void setContact(const std::string& newContact) { contact = newContact; }
};

#endif // PERSON_H
