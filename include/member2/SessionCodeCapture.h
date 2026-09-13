#ifndef MEMBER2_SESSION_CODE_CAPTURE_H
#define MEMBER2_SESSION_CODE_CAPTURE_H

#include "member2/AttendanceCapture.h"

class SessionCodeCapture : public AttendanceCapture {
public:
    void beginSession(AttendanceSession& session) override;
    bool captureNext(CaptureEvent& outEvent) override;
    void endSession() override;

private:
    bool sessionActive_ = false;
};

#endif
