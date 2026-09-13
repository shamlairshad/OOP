#ifndef MEMBER2_ATTENDANCE_REGISTER_H
#define MEMBER2_ATTENDANCE_REGISTER_H

#include "member2/AttendanceCorrection.h"
#include "member2/AttendanceRecord.h"
#include "member2/AttendanceSession.h"
#include <string>
#include <vector>

class AttendanceRegister {
public:
    // Interface Agreement: course code, lecturer ID, and slot are supplied by AttendanceService.
    AttendanceSession& openSession(const std::string& courseCode, const std::string& lecturerId,
                                   const TimeSlot& slot);
    void closeSession(AttendanceSession& session);
    bool alreadyMarked(const std::string& sessionId, const std::string& studentId) const;
    void mark(const AttendanceSession& session, const std::string& studentId,
              AttendanceStatus status, const std::string& method);
    void applyCorrection(const AttendanceCorrection& correction);
    double percentageFor(const std::string& studentId) const;
    const std::vector<AttendanceRecord>& allRecords() const;
    const std::vector<AttendanceCorrection>& allCorrections() const;

private:
    bool ownsSession(const std::string& sessionId) const;
    bool hasRecordFor(const std::string& studentId, const std::string& sessionId) const;
    AttendanceStatus effectiveStatusFor(const AttendanceRecord& record) const;
    std::string makeSessionId();

    unsigned nextSessionNumber_ = 1;
    std::vector<AttendanceRecord> records_;
    std::vector<AttendanceCorrection> corrections_;
    // Do not keep a returned reference after opening another session: vector may reallocate.
    std::vector<AttendanceSession> sessions_;
};

#endif
