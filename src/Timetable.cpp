#include "member2/Timetable.h"

void Timetable::addSlot(const TimeSlot& slot) { slots_.push_back(slot); }
Timetable& Timetable::operator+=(const TimeSlot& slot) { addSlot(slot); return *this; }
bool Timetable::clashesWith(const Timetable& other) const
{
    for (const auto& mine : slots_)
        for (const auto& theirs : other.slots_)
            if (mine && theirs) return true;
    return false;
}
const std::vector<TimeSlot>& Timetable::getSlots() const { return slots_; }
