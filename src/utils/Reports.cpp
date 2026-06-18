/**
 * @file Reports.cpp
 * @brief Implementation of SCMS::Reports and SCMS::Utils namespace functions
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Namespaces, Smart Pointers, Lambdas, STL Algorithms (sort, find_if, copy_if)
 */

#include "Reports.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace SCMS {

    namespace Utils {
        
        bool isValidCNIC(const std::string& cnic) {
            // Standard Pakistani CNIC format: XXXXX-XXXXXXX-X (15 characters)
            if (cnic.length() != 15) return false;
            for (int i = 0; i < 15; ++i) {
                if (i == 5 || i == 13) {
                    if (cnic[i] != '-') return false;
                } else {
                    if (!std::isdigit(cnic[i])) return false;
                }
            }
            return true;
        }

        bool isValidContact(const std::string& contact) {
            // Format: XXXX-XXXXXXX (12 characters)
            if (contact.length() != 12) return false;
            for (int i = 0; i < 12; ++i) {
                if (i == 4) {
                    if (contact[i] != '-') return false;
                } else {
                    if (!std::isdigit(contact[i])) return false;
                }
            }
            return true;
        }

        std::string getCurrentDate() {
            // Fixed date simulation for consistent testing, or we can use time_t.
            // Let's use 2026-06-18 as the system current date
            return "2026-06-18";
        }

        // Helper to convert date to absolute days count
        int dateToDays(int y, int m, int d) {
            if (m < 3) {
                y--;
                m += 12;
            }
            return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m + 2) / 5 + d;
        }

        int daysBetween(const std::string& d1, const std::string& d2) {
            int y1 = 0, m1 = 0, dd1 = 0;
            int y2 = 0, m2 = 0, dd2 = 0;
            char dash = '\0';
            
            std::stringstream ss1(d1);
            ss1 >> y1 >> dash >> m1 >> dash >> dd1;
            
            std::stringstream ss2(d2);
            ss2 >> y2 >> dash >> m2 >> dash >> dd2;

            return dateToDays(y2, m2, dd2) - dateToDays(y1, m1, dd1);
        }
    }

    namespace Reports {

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
        ) {
            std::ofstream reportFile(outputFilePath);
            if (!reportFile.is_open()) {
                std::cerr << "Error: Could not write consolidated report to " << outputFilePath << "\n";
                return;
            }

            reportFile << "================================================================================\n"
                       << "                      HITEC UNIVERSITY CAMPUS STATUS REPORT                     \n"
                       << "                          Date Generated: " << Utils::getCurrentDate() << "                   \n"
                       << "================================================================================\n\n";

            // 1. PERSON REGISTRY
            reportFile << "1. PERSON REGISTRY SUMMARY\n"
                       << "---------------------------\n"
                       << "Total Registered Students: " << students.size() << "\n"
                       << "Total Registered Faculty:  " << faculty.size() << "\n\n";

            reportFile << "Students Details:\n"
                       << std::left << std::setw(15) << "Roll No" 
                       << std::setw(25) << "Name" 
                       << std::setw(6) << "Sem" 
                       << std::setw(6) << "GPA" 
                       << "Contact\n";
            reportFile << "--------------------------------------------------------------------------------\n";
            for (const auto& s : students) {
                reportFile << std::left << std::setw(15) << s->getRollNo()
                           << std::setw(25) << s->getName()
                           << std::setw(6) << s->getSemester()
                           << std::setw(6) << std::fixed << std::setprecision(2) << s->getGPA()
                           << s->getContact() << "\n";
            }
            reportFile << "\n";

            reportFile << "Faculty Details:\n"
                       << std::left << std::setw(15) << "Employee ID" 
                       << std::setw(25) << "Name" 
                       << std::setw(20) << "Department" 
                       << "Designation\n";
            reportFile << "--------------------------------------------------------------------------------\n";
            for (const auto& f : faculty) {
                reportFile << std::left << std::setw(15) << f->getEmployeeID()
                           << std::setw(25) << f->getName()
                           << std::setw(20) << f->getDepartment()
                           << f->getDesignation() << "\n";
            }
            reportFile << "\n\n";

            // 2. COURSE & ENROLLMENT
            reportFile << "2. COURSE REGISTRATION SUMMARY\n"
                       << "-------------------------------\n";
            for (const auto& c : courses) {
                reportFile << "Course: " << c.getCourseCode() << " - " << c.getCourseName() 
                           << " | Credits: " << c.getCreditHours() << "\n"
                           << "  Instructor: " << (c.getInstructor() ? c.getInstructor()->getName() : "None") << "\n"
                           << "  Enrollment: " << c.getEnrolledStudents().size() << "/" << c.getMaxCapacity() 
                           << " (Waitlist size: " << c.getWaitingList().size() << ")\n";
                if (!c.getEnrolledStudents().empty()) {
                    reportFile << "  Enrolled Students: ";
                    for (const auto& s : c.getEnrolledStudents()) {
                        reportFile << s->getRollNo() << " ";
                    }
                    reportFile << "\n";
                }
                reportFile << "\n";
            }
            reportFile << "\n";

            // 3. LIBRARY SYSTEM
            reportFile << "3. LIBRARY Subsystem Status\n"
                       << "----------------------------\n"
                       << "Total Books in Catalog: " << bookLibrary.getItems().size() << "\n"
                       << "Total Journals in Catalog: " << journalLibrary.getItems().size() << "\n\n"
                       << "Books Inventory:\n"
                       << std::left << std::setw(10) << "Item ID" 
                       << std::setw(30) << "Title" 
                       << std::setw(20) << "Author" 
                       << "Copies Available\n"
                       << "--------------------------------------------------------------------------------\n";
            for (const auto& b : bookLibrary.getItems()) {
                reportFile << std::left << std::setw(10) << b.getItemID()
                           << std::setw(30) << b.getTitle().substr(0, 28)
                           << std::setw(20) << b.getAuthor().substr(0, 18)
                           << b.getCopiesAvailable() << "\n";
            }
            reportFile << "\n";

            // 4. HOSTEL MANAGEMENT
            reportFile << "4. HOSTEL ALLOCATION SUMMARY\n"
                       << "-----------------------------\n";
            for (const auto& block : hostelManager.getBlocks()) {
                reportFile << "Hostel Block: " << block.getBlockName() << "\n";
                for (const auto& room : block.getRooms()) {
                    reportFile << "  Room " << room.getRoomNumber() 
                               << " | Type: " << room.getType() 
                               << " | Occupants: " << room.getOccupants().size() << "/" << room.getMaxCapacity() << "\n";
                    if (!room.getOccupants().empty()) {
                        reportFile << "    Occupants Roll Nos: ";
                        for (const auto& occ : room.getOccupants()) {
                            reportFile << occ->getRollNo() << " ";
                        }
                        reportFile << "\n";
                    }
                }
            }
            reportFile << "\n\n";

            // 5. FINANCE SUMMARY
            reportFile << "5. FINANCE & FEE REGISTRATION REPORT\n"
                       << "-------------------------------------\n";
            double totalOutstandingBalance = 0.0;
            double totalCollected = 0.0;
            for (const auto& fr : feeRecords) {
                totalOutstandingBalance += fr.getBalance();
                totalCollected += fr.getTotalPaid();
                reportFile << "Roll No: " << (fr.getStudentRef() ? fr.getStudentRef()->getRollNo() : "N/A")
                           << " | Paid: $" << fr.getTotalPaid()
                           << " | Outstanding: $" << fr.getBalance() << "\n";
            }
            reportFile << "\nTotal Fees Collected:       $" << totalCollected << "\n"
                       << "Total Outstanding Balance:  $" << totalOutstandingBalance << "\n"
                       << "Total Invoices Issued:      " << invoices.size() << "\n";
                       
            reportFile << "\n=================================== END REPORT =================================\n";
            reportFile.close();
            std::cout << "Consolidated campus report saved to " << outputFilePath << "\n";
        }

        // Lambda sorting: sorts students by GPA in descending order
        void sortStudentsByGPA(std::vector<std::shared_ptr<Student>>& students) {
            std::sort(students.begin(), students.end(), [](const std::shared_ptr<Student>& a, const std::shared_ptr<Student>& b) {
                return a->getGPA() > b->getGPA(); // Lambda with captures: compares GPAs
            });
        }

        // Lambda filtering: returns books with 0 copies available (simulating filter overdue/out-of-stock)
        std::vector<Book> getOutOfStockBooks(const Library<Book>& bookLibrary) {
            std::vector<Book> outOfStock;
            const auto& allBooks = bookLibrary.getItems();
            // Lambda with capture by reference to push items
            std::copy_if(allBooks.begin(), allBooks.end(), std::back_inserter(outOfStock), [](const Book& b) {
                return b.getCopiesAvailable() == 0;
            });
            return outOfStock;
        }

        // Lambda searching: matches a student by roll number
        std::shared_ptr<Student> findStudentByRollNo(
            const std::vector<std::shared_ptr<Student>>& students, 
            const std::string& rollNo
        ) {
            // Lambda capturing rollNo by value
            auto it = std::find_if(students.begin(), students.end(), [rollNo](const std::shared_ptr<Student>& s) {
                return s->getRollNo() == rollNo;
            });
            if (it != students.end()) {
                return *it;
            }
            return nullptr;
        }

    } // namespace Reports

} // namespace SCMS
