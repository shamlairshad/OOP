#include "member2/AttendanceCorrection.h"

AttendanceCorrection::AttendanceCorrection(const std::string& studentId, const std::string& sessionId,
                                           const std::string& actingLecturerId, const std::string& reason,
                                           AttendanceStatus newStatus)
    : studentId_(studentId), sessionId_(sessionId), actingLecturerId_(actingLecturerId),
      reason_(reason), newStatus_(newStatus) {}
const std::string& AttendanceCorrection::studentId() const { return studentId_; }
const std::string& AttendanceCorrection::sessionId() const { return sessionId_; }
const std::string& AttendanceCorrection::actingLecturerId() const { return actingLecturerId_; }
const std::string& AttendanceCorrection::reason() const { return reason_; }
AttendanceStatus AttendanceCorrection::newStatus() const { return newStatus_; }
