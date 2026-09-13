#ifndef MEMBER2_ATTENDANCE_SESSION_H
#define MEMBER2_ATTENDANCE_SESSION_H

#include "member2/SessionCode.h"
#include "member2/TimeSlot.h"
#include <ctime>
#include <string>

class AttendanceSession {
public:
    AttendanceSession(const std::string& sessionId, const std::string& courseCode,
                      const std::string& lecturerId, const TimeSlot& slot);
    void open();
    void close();
    bool isOpen() const;
    const std::string& sessionId() const;
    const std::string& courseCode() const;
    const std::string& lecturerId() const;
    const TimeSlot& slot() const;
    std::time_t openTime() const;
    SessionCode& sessionCode();
    const SessionCode& sessionCode() const;

private:
    std::string sessionId_;
    std::string courseCode_;
    std::string lecturerId_;
    TimeSlot slot_;
    std::time_t openTime_ = 0;
    bool open_ = false;
    SessionCode sessionCode_;
};

#endif
