#ifndef MEMBER2_ATTENDANCE_CAPTURE_H
#define MEMBER2_ATTENDANCE_CAPTURE_H

#include <ctime>
#include <string>

class AttendanceSession;

struct CaptureEvent {
    std::string studentId;
    std::string enteredCode;
    std::time_t timestamp = 0;
};

class AttendanceCapture {
public:
    virtual void beginSession(AttendanceSession& session) = 0;
    virtual bool captureNext(CaptureEvent& outEvent) = 0;
    virtual void endSession() = 0;
    virtual ~AttendanceCapture() = default;
};

#endif
