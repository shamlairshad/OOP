#include "member2/AttendanceRegister.h"
#include "member2/AttendanceExceptions.h"
#include <ctime>

AttendanceSession& AttendanceRegister::openSession(const std::string& courseCode, const std::string& lecturerId,
                                                   const TimeSlot& slot)
{
    if (courseCode.empty() || lecturerId.empty()) {
        throw AttendanceException("A course code and lecturer ID are required to open attendance.");
    }
    sessions_.emplace_back(makeSessionId(), courseCode, lecturerId, slot);
    AttendanceSession& session = sessions_.back();
    session.open();
    return session;
}

void AttendanceRegister::closeSession(AttendanceSession& session)
{
    if (!ownsSession(session.sessionId())) throw UnknownSessionException("This session is not managed by this register.");
    session.close();
}

bool AttendanceRegister::alreadyMarked(const std::string& sessionId, const std::string& studentId) const
{ return hasRecordFor(studentId, sessionId); }

void AttendanceRegister::mark(const AttendanceSession& session, const std::string& studentId,
                              AttendanceStatus status, const std::string& method)
{
    if (!ownsSession(session.sessionId())) throw UnknownSessionException("This session is not managed by this register.");
    if (!session.isOpen()) throw SessionClosedException("Session '" + session.sessionId() + "' is closed.");
    if (studentId.empty()) throw AttendanceException("A student ID is required.");
    if (method.empty()) throw AttendanceException("The capture method must be recorded.");
    if (alreadyMarked(session.sessionId(), studentId))
        throw DuplicateAttendanceException("Student '" + studentId + "' is already marked for this session.");
    records_.emplace_back(studentId, session.sessionId(), std::time(nullptr), status, method);
}

void AttendanceRegister::applyCorrection(const AttendanceCorrection& correction)
{
    if (!hasRecordFor(correction.studentId(), correction.sessionId()))
        throw InvalidAttendanceCorrectionException("A correction must refer to an existing attendance record.");
    if (correction.actingLecturerId().empty() || correction.reason().empty())
        throw InvalidAttendanceCorrectionException("A correction needs a lecturer ID and reason.");
    corrections_.push_back(correction); // Append-only: the original record remains unchanged.
}

double AttendanceRegister::percentageFor(const std::string& studentId) const
{
    int total = 0, attended = 0;
    for (const auto& record : records_) {
        if (record.studentId() != studentId) continue;
        ++total;
        if (countsAsAttended(effectiveStatusFor(record))) ++attended;
    }
    return total == 0 ? 0.0 : static_cast<double>(attended) * 100.0 / total;
}

const std::vector<AttendanceRecord>& AttendanceRegister::allRecords() const { return records_; }
const std::vector<AttendanceCorrection>& AttendanceRegister::allCorrections() const { return corrections_; }
bool AttendanceRegister::ownsSession(const std::string& sessionId) const
{ for (const auto& session : sessions_) if (session.sessionId() == sessionId) return true; return false; }
bool AttendanceRegister::hasRecordFor(const std::string& studentId, const std::string& sessionId) const
{ for (const auto& record : records_) if (record.studentId() == studentId && record.sessionId() == sessionId) return true; return false; }
AttendanceStatus AttendanceRegister::effectiveStatusFor(const AttendanceRecord& record) const
{
    AttendanceStatus result = record.status();
    for (const auto& correction : corrections_)
        if (correction.studentId() == record.studentId() && correction.sessionId() == record.sessionId())
            result = correction.newStatus(); // The latest appended correction wins.
    return result;
}
std::string AttendanceRegister::makeSessionId() { return "AS-" + std::to_string(nextSessionNumber_++); }
