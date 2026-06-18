/**
 * @file Person.cpp
 * @brief Implementation of the Abstract Base Class Person
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Constructors, Encapsulation
 */

#include "Person.h"

Person::Person(std::string name, std::string cnic, int age, std::string contact)
    : name(name), cnic(cnic), age(age), contact(contact) {}
