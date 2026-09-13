#ifndef MEMBER2_ATTENDANCE_REPORT_H
#define MEMBER2_ATTENDANCE_REPORT_H

#include <ostream>
#include <string>
#include <vector>

class AttendanceRegister;

void printAttendanceReport(const AttendanceRegister& register_, const std::vector<std::string>& studentIds,
                           std::ostream& output);
void printAllRecords(const AttendanceRegister& register_, std::ostream& output);

#endif
