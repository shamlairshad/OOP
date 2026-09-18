#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class SystemException : public std::exception
{
protected:
    std::string msg;

public:
    explicit SystemException(const std::string& message)
        : msg(message) {}

    const char* what() const noexcept override
    {
        return msg.c_str();
    }

    virtual ~SystemException() = default;
};

// ---------- Authentication ----------

class AuthenticationException : public SystemException
{
public:
    explicit AuthenticationException(const std::string& message)
        : SystemException("[Authentication] " + message) {}
};

// ---------- Persistence / files ----------

class PersistenceException : public SystemException
{
public:
    explicit PersistenceException(const std::string& message)
        : SystemException("[Persistence] " + message) {}
};

class FileNotFoundException : public PersistenceException
{
public:
    explicit FileNotFoundException(const std::string& message)
        : PersistenceException(message) {}
};

class CorruptDataException : public PersistenceException
{
public:
    explicit CorruptDataException(const std::string& message)
        : PersistenceException(message) {}
};

class MalformedCaptureLineException : public PersistenceException
{
public:
    explicit MalformedCaptureLineException(const std::string& message)
        : PersistenceException(message) {}
};

// ---------- Enrolment ----------

class EnrollmentException : public SystemException
{
public:
    explicit EnrollmentException(const std::string& message)
        : SystemException("[Enrollment] " + message) {}
};

class PrerequisiteNotMetException : public EnrollmentException
{
public:
    explicit PrerequisiteNotMetException(const std::string& message)
        : EnrollmentException(message) {}
};

class CourseFullException : public EnrollmentException
{
public:
    explicit CourseFullException(const std::string& message)
        : EnrollmentException(message) {}
};

class AlreadyEnrolledException : public EnrollmentException
{
public:
    explicit AlreadyEnrolledException(const std::string& message)
        : EnrollmentException(message) {}
};

class TimetableClashException : public EnrollmentException
{
public:
    explicit TimetableClashException(const std::string& message)
        : EnrollmentException(message) {}
};

// ---------- Attendance ----------

class AttendanceException : public SystemException
{
public:
    explicit AttendanceException(const std::string& message)
        : SystemException("[Attendance] " + message) {}
};

class SessionClosedException : public AttendanceException
{
public:
    explicit SessionClosedException(const std::string& message)
        : AttendanceException(message) {}
};

class NotEnrolledException : public AttendanceException
{
public:
    explicit NotEnrolledException(const std::string& message)
        : AttendanceException(message) {}
};

class DuplicateAttendanceException : public AttendanceException
{
public:
    explicit DuplicateAttendanceException(const std::string& message)
        : AttendanceException(message) {}
};

#endif