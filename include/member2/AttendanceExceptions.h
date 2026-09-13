#ifndef MEMBER2_ATTENDANCE_EXCEPTIONS_H
#define MEMBER2_ATTENDANCE_EXCEPTIONS_H

#include <exception>
#include <string>

class AttendanceException : public std::exception {
public:
    explicit AttendanceException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }

private:
    std::string message_;
};
class SessionClosedException : public AttendanceException {
public:
    explicit SessionClosedException(const std::string& message) : AttendanceException(message) {}
};
class DuplicateAttendanceException : public AttendanceException {
public:
    explicit DuplicateAttendanceException(const std::string& message) : AttendanceException(message) {}
};
class UnknownSessionException : public AttendanceException {
public:
    explicit UnknownSessionException(const std::string& message) : AttendanceException(message) {}
};
class InvalidAttendanceCorrectionException : public AttendanceException {
public:
    explicit InvalidAttendanceCorrectionException(const std::string& message) : AttendanceException(message) {}
};

#endif
