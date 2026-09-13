#include "member2/AttendanceReport.h"
#include "member2/AttendanceRegister.h"
#include <ostream>

void printAttendanceReport(const AttendanceRegister& register_, const std::vector<std::string>& studentIds,
                           std::ostream& output)
{
    output << "\n===== Attendance Report =====\n";
    for (const auto& studentId : studentIds)
        output << studentId << " : " << register_.percentageFor(studentId) << "% attendance\n";
}

void printAllRecords(const AttendanceRegister& register_, std::ostream& output)
{
    output << "\n===== All Attendance Records =====\n";
    for (const auto& record : register_.allRecords()) output << record << '\n';
}
