#include "member2/SessionCodeCapture.h"
#include "member2/AttendanceSession.h"
#include <ctime>
#include <iostream>
#include <string>

void SessionCodeCapture::beginSession(AttendanceSession& session)
{
    // The non-const reference is intentional: it exactly matches the agreed abstract interface.
    sessionActive_ = session.isOpen();
}

bool SessionCodeCapture::captureNext(CaptureEvent& outEvent)
{
    if (!sessionActive_) return false;
    std::cout << "Enter student ID (blank to stop): ";
    if (!std::getline(std::cin, outEvent.studentId) || outEvent.studentId.empty()) return false;
    std::cout << "Enter session code: ";
    std::getline(std::cin, outEvent.enteredCode);
    outEvent.timestamp = std::time(nullptr);
    return true;
}

void SessionCodeCapture::endSession() { sessionActive_ = false; }
