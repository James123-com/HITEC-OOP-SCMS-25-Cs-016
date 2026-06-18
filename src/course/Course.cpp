#include "Course.h"
#include "../utils/Exceptions.h"
#include <algorithm>
Course::Course() : creditHours(0), instructor(nullptr), maxCapacity(0) {}
Course::Course(std::string courseCode, std::string courseName, int creditHours,
               std::shared_ptr<Faculty> instructor, size_t maxCapacity)
    : courseCode(courseCode), courseName(courseName), creditHours(creditHours),
      instructor(instructor), maxCapacity(maxCapacity) {
    if (instructor) {
        instructor->assignCourseCode(courseCode);
    }
}
void Course::enrollStudent(const std::shared_ptr<Student>& student) {
    if (!student) return;
    for (const auto& s : enrolledStudents) {
        if (s->getRollNo() == student->getRollNo()) return;
    }
    if (enrolledStudents.size() >= maxCapacity) {
        throw SCMS::CapacityExceededException(courseCode, maxCapacity);
    }
    enrolledStudents.push_back(student);
    student->addCourseCode(courseCode);
}
void Course::addWaitingStudent(const std::shared_ptr<Student>& student) {
    if (!student) return;
    for (const auto& s : waitingList) {
        if (s->getRollNo() == student->getRollNo()) return;
    }
    waitingList.push_back(student);
}
void Course::removeStudent(const std::string& rollNo) {
    auto itEnrolled = std::remove_if(enrolledStudents.begin(), enrolledStudents.end(),
        [&rollNo](const std::shared_ptr<Student>& s) {
            return s->getRollNo() == rollNo;
        });
    if (itEnrolled != enrolledStudents.end()) {
        enrolledStudents.erase(itEnrolled, enrolledStudents.end());
    }
    auto itWaiting = std::remove_if(waitingList.begin(), waitingList.end(),
        [&rollNo](const std::shared_ptr<Student>& s) {
            return s->getRollNo() == rollNo;
        });
    if (itWaiting != waitingList.end()) {
        waitingList.erase(itWaiting, waitingList.end());
    }
}
bool Course::operator==(const Course& other) const {
    return this->courseCode == other.courseCode;
}
std::vector<std::shared_ptr<Student>> Course::operator+(const Course& other) const {
    std::vector<std::shared_ptr<Student>> mergedWaitingList = this->waitingList;
    for (const auto& student : other.waitingList) {
        auto it = std::find_if(mergedWaitingList.begin(), mergedWaitingList.end(),
            [&student](const std::shared_ptr<Student>& s) {
                return s->getRollNo() == student->getRollNo();
            });
        if (it == mergedWaitingList.end()) {
            mergedWaitingList.push_back(student);
        }
    }
    return mergedWaitingList;
}
std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "Course Code: " << course.courseCode
       << " | Title: " << course.courseName
       << " | Credit Hours: " << course.creditHours
       << "\nInstructor: " << (course.instructor ? course.instructor->getName() : "Unassigned")
       << " | Capacity: " << course.enrolledStudents.size() << "/" << course.maxCapacity
       << " (Waiting: " << course.waitingList.size() << ")";
    return os;
}
