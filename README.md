# Member 2: Scheduling and Attendance

This folder contains only the Member 2 code: timetable handling, attendance sessions and records,
corrections, capture abstraction, session-code capture, exceptions, and reporting. It uses the C++
headers already covered in class (`iostream`, `ostream`, `string`, `vector`, `ctime`, and `exception`).

## Integration point left deliberately outside this module

`AttendanceService::openAndRun(course, lecturer, slot, capture)` belongs to the agreed service layer.
It should call `AttendanceRegister::openSession(courseCode, lecturerId, slot)`, then call
`capture.beginSession(session)`. For every captured event it must validate
`session.sessionCode().validate(event.enteredCode)` before calling `register.mark(...)`. Finally it
must call `capture.endSession()` and `register.closeSession(session)`.

That code is intentionally not duplicated here because it is the agreed integration boundary with the
other members. The key signatures used by this module are already compatible with it.
