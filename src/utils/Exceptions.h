/**
 * @file Exceptions.h
 * @brief Custom exceptions for the SCMS application
 * @author Syed Muhammad Kashif | Roll No: 25-Cs-016
 * @course CS-202: Object-Oriented Programming
 * @inst HITEC University Taxila
 * @date 2026-06-18
 * 
 * OOP Concepts: Exception Handling, Inheritance, Custom Exception Classes
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace SCMS {

    /**
     * @class SCMSException
     * @brief Base exception class for all SCMS custom exceptions
     */
    class SCMSException : public std::exception {
    protected:
        std::string message;
    public:
        explicit SCMSException(const std::string& msg) : message(msg) {}
        virtual const char* what() const noexcept override {
            return message.c_str();
        }
    };

    /**
     * @class CapacityExceededException
     * @brief Thrown when a course reaches its maximum capacity
     */
    class CapacityExceededException : public SCMSException {
    public:
        explicit CapacityExceededException(const std::string& courseCode, size_t limit)
            : SCMSException("CapacityExceededException: Enrollment limit (" + std::to_string(limit) + 
                            ") reached for Course: " + courseCode) {}
    };

    /**
     * @class OverdueException
     * @brief Thrown when a checked-out library item is returned past its due date
     */
    class OverdueException : public SCMSException {
    private:
        double fineAmount;
    public:
        explicit OverdueException(const std::string& itemID, double fine)
            : SCMSException("OverdueException: Item ID " + itemID + " is returned late. Fine calculated: $" + std::to_string(fine)),
              fineAmount(fine) {}
        
        double getFineAmount() const {
            return fineAmount;
        }
    };

} // namespace SCMS

#endif // EXCEPTIONS_H
