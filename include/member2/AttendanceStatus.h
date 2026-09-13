#ifndef MEMBER2_ATTENDANCE_STATUS_H
#define MEMBER2_ATTENDANCE_STATUS_H

#include <string>

enum class AttendanceStatus : int { PRESENT = 0, ABSENT, LATE, EXCUSED };

std::string statusToString(AttendanceStatus status);
bool countsAsAttended(AttendanceStatus status);

#endif
