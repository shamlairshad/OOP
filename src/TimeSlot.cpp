#include "member2/TimeSlot.h"
#include <ostream>

TimeSlot::TimeSlot(Day day, int startMin, int endMin, const std::string& location)
    : day_(day), startMin_(startMin), endMin_(endMin), location_(location)
{}

bool TimeSlot::operator==(const TimeSlot& other) const
{ return day_ == other.day_ && startMin_ == other.startMin_ && endMin_ == other.endMin_ && location_ == other.location_; }

bool TimeSlot::operator<(const TimeSlot& other) const
{
    if (day_ != other.day_) return day_ < other.day_;
    if (startMin_ != other.startMin_) return startMin_ < other.startMin_;
    if (endMin_ != other.endMin_) return endMin_ < other.endMin_;
    return location_ < other.location_;
}

bool TimeSlot::overlaps(const TimeSlot& other) const
{ return day_ == other.day_ && startMin_ < other.endMin_ && other.startMin_ < endMin_; }

Day TimeSlot::getDay() const { return day_; }
int TimeSlot::getStartMin() const { return startMin_; }
int TimeSlot::getEndMin() const { return endMin_; }
const std::string& TimeSlot::getLocation() const { return location_; }

bool operator&&(const TimeSlot& left, const TimeSlot& right) { return left.overlaps(right); }

std::ostream& operator<<(std::ostream& os, const TimeSlot& slot)
{
    static const char* names[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    const int startHour = slot.getStartMin() / 60;
    const int startMinute = slot.getStartMin() % 60;
    const int endHour = slot.getEndMin() / 60;
    const int endMinute = slot.getEndMin() % 60;
    os << names[static_cast<int>(slot.getDay())] << ' ';
    if (startHour < 10) os << '0';
    os << startHour << ':';
    if (startMinute < 10) os << '0';
    os << startMinute << '-';
    if (endHour < 10) os << '0';
    os << endHour << ':';
    if (endMinute < 10) os << '0';
    os << endMinute << " @ " << slot.getLocation();
    return os;
}
