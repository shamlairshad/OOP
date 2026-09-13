#include "member2/AttendanceStatus.h"

std::string statusToString(AttendanceStatus status)
{
    switch (status) {
    case AttendanceStatus::PRESENT: return "PRESENT";
    case AttendanceStatus::ABSENT:  return "ABSENT";
    case AttendanceStatus::LATE:    return "LATE";
    case AttendanceStatus::EXCUSED: return "EXCUSED";
    }
    return "UNKNOWN";
}

bool countsAsAttended(AttendanceStatus status)
{
    return status == AttendanceStatus::PRESENT ||
           status == AttendanceStatus::LATE ||
           status == AttendanceStatus::EXCUSED;
}
