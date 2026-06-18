/**
 * @file Reports.h
 * @brief Declaration of SCMS::Reports and SCMS::Utils namespaces
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Namespaces (nested), Smart Pointers, Lambdas, STL Algorithm integration
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "../person/Student.h"
#include "../person/Faculty.h"
#include "../course/Course.h"
#include "../library/Library.h"
#include "../library/Book.h"
#include "../library/Journal.h"
#include "../finance/FeeRecord.h"
#include "../finance/Invoice.h"
#include "../hostel/HostelManager.h"
#include <vector>
#include <string>
#include <memory>

namespace SCMS {

    namespace Utils {
        // Validation functions
        bool isValidCNIC(const std::string& cnic);
        bool isValidContact(const std::string& contact);

        // Date utilities
        std::string getCurrentDate();
        int daysBetween(const std::string& d1, const std::string& d2);
    }

    namespace Reports {
        // Consolidated system status generator
        void generateConsolidatedReport(
            const std::vector<std::shared_ptr<Student>>& students,
            const std::vector<std::shared_ptr<Faculty>>& faculty,
            const std::vector<Course>& courses,
            Library<Book>& bookLibrary,
            Library<Journal>& journalLibrary,
            const std::vector<FeeRecord>& feeRecords,
            const std::vector<Invoice>& invoices,
            const HostelManager& hostelManager,
            const std::string& outputFilePath
        );

        // Lambda sorting: sorts students by GPA in descending order
        void sortStudentsByGPA(std::vector<std::shared_ptr<Student>>& students);

        // Lambda filtering: returns books with 0 copies available (simulating filter overdue/out-of-stock)
        std::vector<Book> getOutOfStockBooks(const Library<Book>& bookLibrary);

        // Lambda searching: matches a student by roll number
        std::shared_ptr<Student> findStudentByRollNo(
            const std::vector<std::shared_ptr<Student>>& students, 
            const std::string& rollNo
        );
    }

} // namespace SCMS

#endif // REPORTS_H
