#include "member2/AttendanceRecord.h"
#include <ostream>

unsigned AttendanceRecord::nextRecordId_ = 1;
AttendanceRecord::AttendanceRecord(const std::string& studentId, const std::string& sessionId,
                                   std::time_t timestamp, AttendanceStatus status, const std::string& captureMethod)
    : recordId_(nextRecordId_++), studentId_(studentId), sessionId_(sessionId), timestamp_(timestamp),
      status_(status), captureMethod_(captureMethod) {}
unsigned AttendanceRecord::recordId() const { return recordId_; }
const std::string& AttendanceRecord::studentId() const { return studentId_; }
const std::string& AttendanceRecord::sessionId() const { return sessionId_; }
std::time_t AttendanceRecord::timestamp() const { return timestamp_; }
AttendanceStatus AttendanceRecord::status() const { return status_; }
const std::string& AttendanceRecord::captureMethod() const { return captureMethod_; }
std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record)
{ return os << "Record#" << record.recordId() << " [" << record.studentId() << '/' << record.sessionId() << "] " << statusToString(record.status()) << " via " << record.captureMethod(); }
