#include "member2/AttendanceCorrection.h"
#include "member2/AttendanceRegister.h"
#include "member2/AttendanceReport.h"
#include "member2/Timetable.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    TimeSlot monday(Day::MON, 9 * 60, 10 * 60, "A101");
    TimeSlot overlapping(Day::MON, 9 * 60 + 30, 10 * 60 + 30, "B202");
    Timetable first, second;
    first += monday;
    second += overlapping;

    if (!first.clashesWith(second))
    {
        std::cout << "FAIL: expected overlapping slots to clash\n";
        return 1;
    }
    std::cout << "PASS: clash detection\n";

    AttendanceRegister register_;
    std::string sessionId = register_.openSession("CO2203", "L001", monday);
    AttendanceSession* session = register_.findSession(sessionId);
    if (session == nullptr)
    {
        std::cout << "FAIL: session not found after opening\n";
        return 1;
    }
    std::cout << "PASS: session opened and found\n";

    if (!session->sessionCode().validate(session->sessionCode().value()))
    {
        std::cout << "FAIL: session code did not validate against itself\n";
        return 1;
    }
    std::cout << "PASS: session code self-validates\n";

    register_.mark(*session, "S001", AttendanceStatus::ABSENT, "SessionCodeCapture");
    register_.applyCorrection(AttendanceCorrection("S001", session->sessionId(), "L001",
                                                    "Lecturer verified attendance.", AttendanceStatus::PRESENT));

    if (register_.percentageFor("S001") != 100.0)
    {
        std::cout << "FAIL: expected 100% after correction, got "
                   << register_.percentageFor("S001") << "\n";
        return 1;
    }
    std::cout << "PASS: correction raised attendance to 100%\n";

    register_.closeSession(*session);

    std::ofstream reportFile("smoke_test_report.tmp");
    printAttendanceReport(register_, {"S001"}, reportFile);
    reportFile.close();

    std::string reportContents;
    std::ifstream in("smoke_test_report.tmp");
    std::string line;
    while (std::getline(in, line))
    {
        reportContents += line;
        reportContents += '\n';
    }

    if (reportContents.find("100") == std::string::npos)
    {
        std::cout << "FAIL: report did not contain expected 100% figure\n";
        return 1;
    }
    std::cout << "PASS: report contains expected figure\n";

    std::cout << "\nAll smoke tests passed.\n";
    return 0;
}