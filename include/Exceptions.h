#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class UniversityException : public std::exception
{
protected:
    std::string msg;

public:
    explicit UniversityException(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
    virtual ~UniversityException() = default;
};

#endif