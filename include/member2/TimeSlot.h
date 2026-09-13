#ifndef MEMBER2_TIME_SLOT_H
#define MEMBER2_TIME_SLOT_H

#include "member2/Day.h"
#include <ostream>
#include <string>

class TimeSlot {
public:
    TimeSlot(Day day, int startMin, int endMin, const std::string& location);

    bool operator==(const TimeSlot& other) const;
    bool operator<(const TimeSlot& other) const;
    bool overlaps(const TimeSlot& other) const;

    Day getDay() const;
    int getStartMin() const;
    int getEndMin() const;
    const std::string& getLocation() const;

private:
    Day day_;
    int startMin_;
    int endMin_;
    std::string location_;
};

bool operator&&(const TimeSlot& left, const TimeSlot& right);
std::ostream& operator<<(std::ostream& os, const TimeSlot& slot);

#endif
