#include "member2/AttendanceCorrection.h"
#include "member2/AttendanceRegister.h"
#include "member2/AttendanceReport.h"
#include "member2/Timetable.h"
#include <cassert>
#include <sstream>

int main()
{
    TimeSlot monday(Day::MON, 9 * 60, 10 * 60, "A101");
    TimeSlot overlapping(Day::MON, 9 * 60 + 30, 10 * 60 + 30, "B202");
    Timetable first, second;
    first += monday;
    second += overlapping;
    assert(first.clashesWith(second));

    AttendanceRegister register_;
    AttendanceSession& session = register_.openSession("CO2203", "L001", monday);
    assert(session.sessionCode().validate(session.sessionCode().value()));
    register_.mark(session, "S001", AttendanceStatus::ABSENT, "SessionCodeCapture");
    register_.applyCorrection(AttendanceCorrection("S001", session.sessionId(), "L001", "Lecturer verified attendance.", AttendanceStatus::PRESENT));
    assert(register_.percentageFor("S001") == 100.0);
    register_.closeSession(session);

    std::ostringstream report;
    printAttendanceReport(register_, {"S001"}, report);
    assert(report.str().find("100") != std::string::npos);
}
