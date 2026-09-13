#ifndef MEMBER2_TIMETABLE_H
#define MEMBER2_TIMETABLE_H

#include "member2/TimeSlot.h"
#include <vector>

class Timetable {
public:
    void addSlot(const TimeSlot& slot);
    Timetable& operator+=(const TimeSlot& slot);
    bool clashesWith(const Timetable& other) const;
    const std::vector<TimeSlot>& getSlots() const;

private:
    std::vector<TimeSlot> slots_;
};

#endif
