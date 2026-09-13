#ifndef MEMBER2_ATTENDANCE_RECORD_H
#define MEMBER2_ATTENDANCE_RECORD_H

#include "member2/AttendanceStatus.h"
#include <ctime>
#include <ostream>
#include <string>

class AttendanceRecord {
public:
    AttendanceRecord(const std::string& studentId, const std::string& sessionId,
                     std::time_t timestamp, AttendanceStatus status, const std::string& captureMethod);
    unsigned recordId() const;
    const std::string& studentId() const;
    const std::string& sessionId() const;
    std::time_t timestamp() const;
    AttendanceStatus status() const;
    const std::string& captureMethod() const;

private:
    static unsigned nextRecordId_;
    unsigned recordId_;
    std::string studentId_;
    std::string sessionId_;
    std::time_t timestamp_;
    AttendanceStatus status_;
    std::string captureMethod_;
};

std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record);

#endif
