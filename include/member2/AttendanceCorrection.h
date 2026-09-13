#ifndef MEMBER2_ATTENDANCE_CORRECTION_H
#define MEMBER2_ATTENDANCE_CORRECTION_H

#include "member2/AttendanceStatus.h"
#include <string>

class AttendanceCorrection {
public:
    AttendanceCorrection(const std::string& studentId, const std::string& sessionId,
                         const std::string& actingLecturerId, const std::string& reason,
                         AttendanceStatus newStatus);
    const std::string& studentId() const;
    const std::string& sessionId() const;
    const std::string& actingLecturerId() const;
    const std::string& reason() const;
    AttendanceStatus newStatus() const;

private:
    std::string studentId_;
    std::string sessionId_;
    std::string actingLecturerId_;
    std::string reason_;
    AttendanceStatus newStatus_;
};

#endif
