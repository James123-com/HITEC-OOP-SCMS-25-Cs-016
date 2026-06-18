/**
 * @file main.cpp
 * @brief Interactive CLI menu and entry point for the SCMS application
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Runtime Polymorphism, Smart Pointers, File I/O, Exception Handling, Lambdas, Move Semantics
 */

#include "person/Person.h"
#include "person/Student.h"
#include "person/GradStudent.h"
#include "person/Faculty.h"
#include "person/Staff.h"
#include "course/Course.h"
#include "course/Enrollment.h"
#include "library/LibraryItem.h"
#include "library/Book.h"
#include "library/Journal.h"
#include "library/Library.h"
#include "finance/FeeRecord.h"
#include "finance/Invoice.h"
#include "hostel/HostelManager.h"
#include "utils/Exceptions.h"
#include "utils/Reports.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

// Global catalogs and lists (using shared_ptr for automatic memory management)
std::vector<std::shared_ptr<Student>> studentsList;
std::vector<std::shared_ptr<Faculty>> facultyList;
std::vector<std::shared_ptr<Staff>> staffList;
std::vector<Course> coursesList;
Library<Book> bookCatalog;
Library<Journal> journalCatalog;
std::vector<FeeRecord> feeRecordsList;
std::vector<Invoice> invoicesList;
std::unique_ptr<HostelManager> hostelSubsystem;

// Track library checkouts: rollNo -> vector of itemIDs
std::map<std::string, std::vector<std::pair<std::string, std::string>>> issuedItemsTracker; // rollNo -> vector<pair<itemID, dueDate>>

// Helper to seed students from CSV
void seedStudents(const std::string& filepath) {
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open students seed file: " << filepath << "\n";
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string roll, name, cnic, ageStr, contact, semStr, gpaStr;
        
        std::getline(ss, roll, ',');
        std::getline(ss, name, ',');
        std::getline(ss, cnic, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, contact, ',');
        std::getline(ss, semStr, ',');
        std::getline(ss, gpaStr, ',');

        try {
            int age = std::stoi(ageStr);
            int sem = std::stoi(semStr);
            double gpa = std::stod(gpaStr);
            studentsList.push_back(std::make_shared<Student>(name, cnic, age, contact, roll, sem, gpa));
        } catch (...) {
            // Skip invalid records
        }
    }
    inFile.close();
    std::cout << "[Seed] Successfully loaded " << studentsList.size() << " students from CSV.\n";
}

// Helper to initialize other components
void initSubsystems() {
    // 1. Load library catalogs
    bookCatalog.loadFromCSV("data/library_catalog.csv");
    journalCatalog.loadFromCSV("data/library_catalog.csv");
    std::cout << "[Seed] Loaded " << bookCatalog.getItems().size() << " books and " 
              << journalCatalog.getItems().size() << " journals from database.\n";

    // 2. Add some faculty members
    facultyList.push_back(std::make_shared<Faculty>("Dr. Muhammad Ali", "37405-1111111-1", 45, "0300-1112223", "F001", "Computer Science", "Professor"));
    facultyList.push_back(std::make_shared<Faculty>("Dr. Sadia Khan", "37405-2222222-2", 38, "0312-3334445", "F002", "Software Engineering", "Associate Prof."));
    facultyList.push_back(std::make_shared<Faculty>("Engr. Zainab", "37405-3333333-2", 29, "0321-5556667", "F003", "Computer Science", "Lecturer"));

    // 3. Add some staff members
    staffList.push_back(std::make_shared<Staff>("Kamran Hashmi", "37405-4444444-1", 35, "0333-7778889", "S001", "Lab Attendant", 45000.0));
    staffList.push_back(std::make_shared<Staff>("Farhan Shah", "37405-5555555-1", 40, "0345-9990001", "S002", "Librarian", 55000.0));

    // 4. Create courses
    coursesList.push_back(Course("CS-202", "Object-Oriented Programming", 4, facultyList[0], 3)); // small capacity (3) to test exceptions
    coursesList.push_back(Course("SE-210", "Software Requirements Eng", 3, facultyList[1], 40));
    coursesList.push_back(Course("CS-101", "Intro to Programming", 3, facultyList[2], 50));

    // 5. Initialize hostel subsystem
    hostelSubsystem = std::make_unique<HostelManager>("Ghazali Hostel Block Services");
    HostelBlock blockA("Jinnah Hall");
    blockA.addRoom(Room(101, "single", 1));
    blockA.addRoom(Room(102, "double", 1));
    blockA.addRoom(Room(103, "triple", 1));
    hostelSubsystem->addBlock(blockA);

    // 6. Create default Fee Records for students
    for (const auto& student : studentsList) {
        // base fee: $50000, hostel: $15000, library fine: $0
        feeRecordsList.push_back(FeeRecord(student, 50000.0, 15000.0, 0.0));
    }
}

// Display Person polymorphic directory
void displayPersonDirectory() {
    std::cout << "\n--- POLYMORPHIC PERSON DIRECTORY ---\n";
    std::cout << "1. Display All Students (Sorted by GPA)\n";
    std::cout << "2. Display All Faculty Members\n";
    std::cout << "3. Display All Staff Members\n";
    std::cout << "4. Add a Graduate Student (Multi-level Inheritance)\n";
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Lambda sort students list
        auto sortedStudents = studentsList;
        SCMS::Reports::sortStudentsByGPA(sortedStudents);
        std::cout << "\nRegistered Students (Sorted by GPA):\n";
        for (const auto& s : sortedStudents) {
            // Polymorphic function dispatch via Person pointer/ref
            s->displayInfo(); 
        }
    } else if (choice == 2) {
        std::cout << "\nRegistered Faculty:\n";
        for (const auto& f : facultyList) {
            f->displayInfo();
        }
    } else if (choice == 3) {
        std::cout << "\nRegistered Staff:\n";
        for (const auto& st : staffList) {
            st->displayInfo();
        }
    } else if (choice == 4) {
        std::string name, cnic, contact, roll, topic, supervisor;
        int age, semester;
        double gpa;
        std::cout << "Enter Name: "; std::cin.ignore(); std::getline(std::cin, name);
        std::cout << "Enter CNIC (XXXXX-XXXXXXX-X): "; std::cin >> cnic;
        if (!SCMS::Utils::isValidCNIC(cnic)) {
            std::cout << "Invalid CNIC Format! Aborting.\n";
            return;
        }
        std::cout << "Enter Age: "; std::cin >> age;
        std::cout << "Enter Contact (XXXX-XXXXXXX): "; std::cin >> contact;
        if (!SCMS::Utils::isValidContact(contact)) {
            std::cout << "Invalid Contact Format! Aborting.\n";
            return;
        }
        std::cout << "Enter Roll Number: "; std::cin >> roll;
        std::cout << "Enter Semester: "; std::cin >> semester;
        std::cout << "Enter GPA: "; std::cin >> gpa;
        std::cout << "Enter Research Topic: "; std::cin.ignore(); std::getline(std::cin, topic);
        std::cout << "Enter Supervisor Name: "; std::getline(std::cin, supervisor);

        // Add Graduate Student
        auto gs = std::make_shared<GradStudent>(name, cnic, age, contact, roll, semester, gpa, topic, supervisor);
        studentsList.push_back(gs);
        feeRecordsList.push_back(FeeRecord(gs, 55000.0, 15000.0, 0.0)); // grad students fee slightly higher
        std::cout << "Graduate Student registered successfully under multi-level inheritance model!\n";
    }
}

// Course Enrollment management
void manageCourseEnrollments() {
    std::cout << "\n--- COURSE & ENROLLMENT MANAGEMENT ---\n"
              << "1. List All Courses (Overloaded <<)\n"
              << "2. Register/Enroll Student in Course (Enforces Capacity, triggers Custom Exceptions)\n"
              << "3. Test Overloaded + (Merge Course Waitlists)\n"
              << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "\nOffered Courses:\n";
        for (const auto& course : coursesList) {
            std::cout << course << "\n-----------------------------\n"; // Calls overloaded << friend operator
        }
    } else if (choice == 2) {
        std::string roll, code;
        std::cout << "Enter Student Roll No: "; std::cin >> roll;
        auto student = SCMS::Reports::findStudentByRollNo(studentsList, roll);
        if (!student) {
            std::cout << "Student not found!\n";
            return;
        }

        std::cout << "Enter Course Code (e.g. CS-202): "; std::cin >> code;
        auto it = std::find_if(coursesList.begin(), coursesList.end(), [&code](const Course& c) {
            return c.getCourseCode() == code;
        });

        if (it == coursesList.end()) {
            std::cout << "Course not found!\n";
            return;
        }

        try {
            it->enrollStudent(student);
            std::cout << "Successfully enrolled " << student->getName() << " in course " << code << ".\n";
        } catch (const SCMS::CapacityExceededException& ex) {
            std::cout << "\n[!] Exception Caught: " << ex.what() << "\n";
            std::cout << "Would you like to add student to the Course waiting list? (y/n): ";
            char wl;
            std::cin >> wl;
            if (wl == 'y' || wl == 'Y') {
                it->addWaitingStudent(student);
                std::cout << "Student added to waiting list.\n";
            }
        }
    } else if (choice == 3) {
        std::cout << "\nWaitlist Merge Demonstration:\n";
        // Create two courses with waiting students
        Course tempCourse1("TEMP-1", "Temp Course 1", 3, nullptr, 1);
        Course tempCourse2("TEMP-2", "Temp Course 2", 3, nullptr, 1);
        
        if (studentsList.size() >= 4) {
            tempCourse1.addWaitingStudent(studentsList[0]);
            tempCourse1.addWaitingStudent(studentsList[1]);
            tempCourse2.addWaitingStudent(studentsList[2]);
            tempCourse2.addWaitingStudent(studentsList[3]);
            
            std::cout << "Waitlist of Temp Course 1: ";
            for (const auto& s : tempCourse1.getWaitingList()) std::cout << s->getRollNo() << " ";
            std::cout << "\nWaitlist of Temp Course 2: ";
            for (const auto& s : tempCourse2.getWaitingList()) std::cout << s->getRollNo() << " ";
            
            // Overloaded operator +
            std::cout << "\nMerging waitlists using '+' operator...\n";
            std::vector<std::shared_ptr<Student>> merged = tempCourse1 + tempCourse2;
            std::cout << "Merged Waitlist: ";
            for (const auto& s : merged) {
                std::cout << s->getRollNo() << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "Not enough students in catalog to run this demonstration.\n";
        }
    }
}

// Library Management Subsystem
void manageLibrary() {
    std::cout << "\n--- LIBRARY SYSTEM ---\n"
              << "1. Search Book/Journal by Title (Template Function)\n"
              << "2. Checkout Library Item (Track Issued Items)\n"
              << "3. Return Library Item (Triggers late-returns check & custom OverdueException)\n"
              << "4. List All Library Items\n"
              << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cin.ignore();
        std::string title;
        std::cout << "Enter Title to search: ";
        std::getline(std::cin, title);

        // search generically
        Book* bookMatch = bookCatalog.searchByTitle<Book>(title);
        Journal* journalMatch = journalCatalog.searchByTitle<Journal>(title);

        if (bookMatch) {
            std::cout << "\nFound Book:\n"
                      << "ID: " << bookMatch->getItemID() << " | Title: " << bookMatch->getTitle()
                      << " | Author: " << bookMatch->getAuthor() << " | ISBN: " << bookMatch->getISBN()
                      << " | Copies Available: " << bookMatch->getCopiesAvailable() << "\n";
        } else if (journalMatch) {
            std::cout << "\nFound Journal:\n"
                      << "ID: " << journalMatch->getItemID() << " | Title: " << journalMatch->getTitle()
                      << " | ISSN: " << journalMatch->getISSN() << " | Vol: " << journalMatch->getVolume() << "\n";
        } else {
            std::cout << "No matching library item found.\n";
        }
    } else if (choice == 2) {
        std::string roll, itemID, dueDate;
        std::cout << "Enter Student Roll No: "; std::cin >> roll;
        auto student = SCMS::Reports::findStudentByRollNo(studentsList, roll);
        if (!student) {
            std::cout << "Student not found!\n";
            return;
        }

        std::cout << "Enter Item ID to checkout (e.g. B001, J001): "; std::cin >> itemID;
        std::cout << "Enter Due Date (YYYY-MM-DD): "; std::cin >> dueDate;

        Book* book = bookCatalog.findByID(itemID);
        Journal* journal = journalCatalog.findByID(itemID);

        try {
            if (book) {
                book->checkout(roll);
            } else if (journal) {
                journal->checkout(roll);
            } else {
                std::cout << "Item not found in catalog!\n";
                return;
            }
            // Add to tracker
            issuedItemsTracker[roll].push_back({itemID, dueDate});
        } catch (const std::exception& ex) {
            std::cout << "Checkout failed: " << ex.what() << "\n";
        }
    } else if (choice == 3) {
        std::string roll, itemID, returnDate;
        std::cout << "Enter Student Roll No: "; std::cin >> roll;
        std::cout << "Enter Item ID: "; std::cin >> itemID;
        std::cout << "Enter Return Date (YYYY-MM-DD): "; std::cin >> returnDate;

        auto& list = issuedItemsTracker[roll];
        auto it = std::find_if(list.begin(), list.end(), [&itemID](const std::pair<std::string, std::string>& p) {
            return p.first == itemID;
        });

        if (it == list.end()) {
            std::cout << "No checkout record found for this student and item.\n";
            return;
        }

        std::string dueDate = it->second;
        list.erase(it); // Remove record

        Book* book = bookCatalog.findByID(itemID);
        Journal* journal = journalCatalog.findByID(itemID);
        if (book) book->returnItem();
        if (journal) journal->returnItem();

        // Calculate fine
        int daysLate = SCMS::Utils::daysBetween(dueDate, returnDate);
        if (daysLate > 0) {
            double fine = daysLate * 5.0; // $5 per day fine
            // Find student's FeeRecord and apply fine
            for (auto& fr : feeRecordsList) {
                if (fr.getStudentRef() && fr.getStudentRef()->getRollNo() == roll) {
                    fr.addFine(fine);
                    break;
                }
            }
            // Throw custom exception to demonstrate custom exception flow
            try {
                throw SCMS::OverdueException(itemID, fine);
            } catch (const SCMS::OverdueException& ex) {
                std::cout << "\n[!] Exception Caught: " << ex.what() << "\n";
                std::cout << "Fine of $" << fine << " has been added to Student's FeeRecord.\n";
            }
        } else {
            std::cout << "Returned on time. No fine applied.\n";
        }
    } else if (choice == 4) {
        std::cout << "\n--- ALL CATALOG ITEMS ---\n";
        std::cout << "Books:\n";
        for (const auto& b : bookCatalog.getItems()) {
            std::cout << " - ID: " << b.getItemID() << " | Title: " << b.getTitle() 
                      << " | Copies Available: " << b.getCopiesAvailable() << "\n";
        }
        std::cout << "\nJournals:\n";
        for (const auto& j : journalCatalog.getItems()) {
            std::cout << " - ID: " << j.getItemID() << " | Title: " << j.getTitle() 
                      << " | Checked Out: " << (j.isCheckedOut() ? "Yes" : "No") << "\n";
        }
    }
}

// Finance management
void manageFinance() {
    std::cout << "\n--- FEE & FINANCE MANAGEMENT ---\n"
              << "1. Print Student Fee Balances & Record Payments (Overloaded -=)\n"
              << "2. Generate Invoice & Demo Move Semantics (Rule of Five)\n"
              << "3. Demonstrate Deep Copy on FeeRecord (Rule of Three)\n"
              << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "\nOutstanding Balances:\n";
        for (auto& fr : feeRecordsList) {
            if (fr.getStudentRef()) {
                std::cout << "Student: " << fr.getStudentRef()->getName() 
                          << " (" << fr.getStudentRef()->getRollNo() << ")\n"
                          << "  Semester Fee: $" << fr.getSemesterFee()
                          << " | Hostel: $" << fr.getHostelFee()
                          << " | Library Fine: $" << fr.getLibraryFine()
                          << " | Total Paid: $" << fr.getTotalPaid()
                          << " | Outstanding: $" << fr.getBalance() << "\n";
            }
        }

        std::string roll;
        double amount;
        std::cout << "\nEnter student roll number to record payment: ";
        std::cin >> roll;
        auto it = std::find_if(feeRecordsList.begin(), feeRecordsList.end(), [&roll](const FeeRecord& fr) {
            return fr.getStudentRef() && fr.getStudentRef()->getRollNo() == roll;
        });

        if (it != feeRecordsList.end()) {
            std::cout << "Enter payment amount: $";
            std::cin >> amount;
            // Overloaded -= operator
            *it -= amount; 
        } else {
            std::cout << "Student FeeRecord not found.\n";
        }
    } else if (choice == 2) {
        std::cin.ignore();
        std::string date, item;
        std::vector<std::string> items;
        double total = 0.0;
        
        std::cout << "Enter Invoice Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        std::cout << "Enter line item details: ";
        std::getline(std::cin, item);
        items.push_back(item);
        std::cout << "Enter total amount: $";
        std::cin >> total;

        std::cout << "\n[Demo] Creating a temporary invoice source...\n";
        Invoice tempInvoice(date, items, total);
        
        std::cout << "\n[Demo] Moving the temporary invoice using Move Semantics (Rule of Five)...\n";
        // Invoking move constructor
        Invoice movedInvoice = std::move(tempInvoice); 
        
        std::cout << "\nMoved Invoice Output (Dynamic Display):\n";
        std::cout << movedInvoice; // prints using overloaded << friend function

        invoicesList.push_back(movedInvoice);
        std::cout << "Invoice registered in central accounting. Current counter value: " 
                  << Invoice::getInvoiceCounter() << "\n";
    } else if (choice == 3) {
        std::cout << "\n[Demo] Deep Copy validation for FeeRecord (Rule of Three):\n";
        if (!feeRecordsList.empty()) {
            std::cout << "Creating deep copy of the first FeeRecord...\n";
            // Invokes deep copy constructor
            FeeRecord copyRecord(feeRecordsList[0]); 
            
            std::cout << "Modifying copied record's details to prove independence...\n";
            copyRecord.setSemesterFee(99999.0);
            
            std::cout << "Original record balance: $" << feeRecordsList[0].getBalance() << "\n";
            std::cout << "Copied record balance:   $" << copyRecord.getBalance() << "\n";
            std::cout << "Deep copy verification successful! Modifying the copy did not affect the original record.\n";
        } else {
            std::cout << "No FeeRecords available to duplicate.\n";
        }
    }
}

// Hostel allocation management
void manageHostel() {
    std::cout << "\n--- HOSTEL ROOM ALLOCATION ---\n"
              << "1. Allocate Student to Room\n"
              << "2. Vacate Student from Room\n"
              << "3. Generate Occupancy Report (Polymorphic Multiple Inheritance)\n"
              << "Enter choice: ";
    int choice;
    std::cin >> choice;

    auto& blocks = hostelSubsystem->getBlocks();
    if (blocks.empty()) {
        std::cout << "No blocks initialized.\n";
        return;
    }

    if (choice == 1) {
        std::string roll;
        int roomNo;
        std::cout << "Enter Student Roll No: "; std::cin >> roll;
        auto student = SCMS::Reports::findStudentByRollNo(studentsList, roll);
        if (!student) {
            std::cout << "Student not found!\n";
            return;
        }

        std::cout << "Enter Room Number to allocate: "; std::cin >> roomNo;
        Room* room = blocks[0].findRoom(roomNo);
        if (!room) {
            std::cout << "Room " << roomNo << " not found in Jinnah Hall!\n";
            return;
        }

        hostelSubsystem->allocateRoom(*room, student);
    } else if (choice == 2) {
        std::string roll;
        int roomNo;
        std::cout << "Enter Student Roll No: "; std::cin >> roll;
        auto student = SCMS::Reports::findStudentByRollNo(studentsList, roll);
        if (!student) {
            std::cout << "Student not found!\n";
            return;
        }

        std::cout << "Enter Room Number: "; std::cin >> roomNo;
        Room* room = blocks[0].findRoom(roomNo);
        if (!room) {
            std::cout << "Room " << roomNo << " not found in Jinnah Hall!\n";
            return;
        }

        hostelSubsystem->vacateRoom(*room, student);
    } else if (choice == 3) {
        // Polymorphic call using top interface reference
        const Reportable& rep = *hostelSubsystem;
        rep.generateReport(); 
    }
}

int main() {
    std::cout << "========================================================\n"
              << "     SMART CAMPUS MANAGEMENT SYSTEM (SCMS) INITIALIZER   \n"
              << "========================================================\n";

    // 1. Seed data
    seedStudents("data/students.csv");
    initSubsystems();

    bool running = true;
    while (running) {
        std::cout << "\n=================== SCMS MAIN MENU ===================\n"
                  << "1. Person Hierarchy Subsystem (Students, Faculty, Staff)\n"
                  << "2. Course & Enrollment Subsystem\n"
                  << "3. Library Management Subsystem (CSV & File I/O)\n"
                  << "4. Finance & Fee Subsystem (Rule of Three/Five)\n"
                  << "5. Hostel Management Subsystem (Diamond Inheritance)\n"
                  << "6. Generate Consolidated State Report (Export)\n"
                  << "7. Save Catalog & Exit\n"
                  << "======================================================\n"
                  << "Enter your choice (1-7): ";
        
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

        switch (choice) {
            case 1:
                displayPersonDirectory();
                break;
            case 2:
                manageCourseEnrollments();
                break;
            case 3:
                manageLibrary();
                break;
            case 4:
                manageFinance();
                break;
            case 5:
                manageHostel();
                break;
            case 6:
                SCMS::Reports::generateConsolidatedReport(
                    studentsList, facultyList, coursesList, 
                    bookCatalog, journalCatalog, feeRecordsList, 
                    invoicesList, *hostelSubsystem, "data/campus_report.txt"
                );
                break;
            case 7:
                std::cout << "Saving library catalog back to CSV data files...\n";
                bookCatalog.saveToCSV("data/library_catalog.csv");
                journalCatalog.saveToCSV("data/library_catalog.csv");
                std::cout << "Library databases saved. Exiting SCMS. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option! Please choose between 1 and 7.\n";
                break;
        }
    }

    return 0;
}
