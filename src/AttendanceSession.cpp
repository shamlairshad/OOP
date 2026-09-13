#include "member2/AttendanceSession.h"

AttendanceSession::AttendanceSession(const std::string& sessionId, const std::string& courseCode,
                                     const std::string& lecturerId, const TimeSlot& slot)
    : sessionId_(sessionId), courseCode_(courseCode), lecturerId_(lecturerId), slot_(slot) {}
void AttendanceSession::open() { openTime_ = std::time(nullptr); open_ = true; sessionCode_.generate(); }
void AttendanceSession::close() { open_ = false; sessionCode_.deactivate(); }
bool AttendanceSession::isOpen() const { return open_; }
const std::string& AttendanceSession::sessionId() const { return sessionId_; }
const std::string& AttendanceSession::courseCode() const { return courseCode_; }
const std::string& AttendanceSession::lecturerId() const { return lecturerId_; }
const TimeSlot& AttendanceSession::slot() const { return slot_; }
std::time_t AttendanceSession::openTime() const { return openTime_; }
SessionCode& AttendanceSession::sessionCode() { return sessionCode_; }
const SessionCode& AttendanceSession::sessionCode() const { return sessionCode_; }
