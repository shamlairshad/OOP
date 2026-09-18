#include "member2/AttendanceRegister.h"
#include "Exceptions.h"
#include <ctime>

std::string AttendanceRegister::openSession(
    const std::string& courseCode,
    const std::string& lecturerId,
    const TimeSlot& slot)
{
    if (courseCode.empty() || lecturerId.empty())
    {
        throw AttendanceException(
            "A course code and lecturer ID are required to open attendance.");
    }

    std::string newId = makeSessionId();

    sessions_.emplace_back(newId, courseCode, lecturerId, slot);
    sessions_.back().open();

    return newId;
}

AttendanceSession* AttendanceRegister::findSession(
    const std::string& sessionId)
{
    for (auto& session : sessions_)
    {
        if (session.sessionId() == sessionId)
        {
            return &session;
        }
    }

    return nullptr;
}

const AttendanceSession* AttendanceRegister::findSession(
    const std::string& sessionId) const
{
    for (const auto& session : sessions_)
    {
        if (session.sessionId() == sessionId)
        {
            return &session;
        }
    }

    return nullptr;
}

void AttendanceRegister::closeSession(AttendanceSession& session)
{
    if (!ownsSession(session.sessionId()))
    {
        throw AttendanceException(
            "This session is not managed by this register.");
    }

    session.close();
}

bool AttendanceRegister::alreadyMarked(
    const std::string& sessionId,
    const std::string& studentId) const
{
    return hasRecordFor(studentId, sessionId);
}

void AttendanceRegister::mark(
    const AttendanceSession& session,
    const std::string& studentId,
    AttendanceStatus status,
    const std::string& method)
{
    if (!ownsSession(session.sessionId()))
    {
        throw AttendanceException(
            "This session is not managed by this register.");
    }

    if (!session.isOpen())
    {
        throw SessionClosedException(
            "Session '" + session.sessionId() + "' is closed.");
    }

    if (studentId.empty())
    {
        throw AttendanceException("A student ID is required.");
    }

    if (method.empty())
    {
        throw AttendanceException(
            "The capture method must be recorded.");
    }

    if (alreadyMarked(session.sessionId(), studentId))
    {
        throw DuplicateAttendanceException(
            "Student '" + studentId +
            "' is already marked for this session.");
    }

    records_.emplace_back(
        studentId,
        session.sessionId(),
        std::time(nullptr),
        status,
        method);
}

void AttendanceRegister::applyCorrection(
    const AttendanceCorrection& correction)
{
    if (!hasRecordFor(correction.studentId(), correction.sessionId()))
    {
        throw AttendanceException(
            "A correction must refer to an existing attendance record.");
    }

    if (correction.actingLecturerId().empty() ||
        correction.reason().empty())
    {
        throw AttendanceException(
            "A correction needs a lecturer ID and reason.");
    }

    // The original AttendanceRecord stays unchanged.
    corrections_.push_back(correction);
}

double AttendanceRegister::percentageFor(
    const std::string& studentId) const
{
    int total = 0;
    int attended = 0;

    for (const auto& record : records_)
    {
        if (record.studentId() != studentId)
        {
            continue;
        }

        ++total;

        if (countsAsAttended(effectiveStatusFor(record)))
        {
            ++attended;
        }
    }

    if (total == 0)
    {
        return 0.0;
    }

    return static_cast<double>(attended) * 100.0 / total;
}

const std::vector<AttendanceRecord>&
AttendanceRegister::allRecords() const
{
    return records_;
}

const std::vector<AttendanceCorrection>&
AttendanceRegister::allCorrections() const
{
    return corrections_;
}

bool AttendanceRegister::ownsSession(
    const std::string& sessionId) const
{
    for (const auto& session : sessions_)
    {
        if (session.sessionId() == sessionId)
        {
            return true;
        }
    }

    return false;
}

bool AttendanceRegister::hasRecordFor(
    const std::string& studentId,
    const std::string& sessionId) const
{
    for (const auto& record : records_)
    {
        if (record.studentId() == studentId &&
            record.sessionId() == sessionId)
        {
            return true;
        }
    }

    return false;
}

AttendanceStatus AttendanceRegister::effectiveStatusFor(
    const AttendanceRecord& record) const
{
    AttendanceStatus result = record.status();

    for (const auto& correction : corrections_)
    {
        if (correction.studentId() == record.studentId() &&
            correction.sessionId() == record.sessionId())
        {
            // The latest correction becomes the effective status.
            result = correction.newStatus();
        }
    }

    return result;
}

std::string AttendanceRegister::makeSessionId()
{
    return "AS-" + std::to_string(nextSessionNumber_++);
}