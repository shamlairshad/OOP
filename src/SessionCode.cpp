#include "member2/SessionCode.h"
#include <ctime>

void SessionCode::generate()
{
    // Simple classroom code. It can later be replaced if the group agrees on a stronger method.
    code_ = "CODE" + std::to_string(std::time(nullptr) % 1000000);
    active_ = true;
}

bool SessionCode::validate(const std::string& enteredCode) const { return active_ && enteredCode == code_; }
const std::string& SessionCode::value() const { return code_; }
void SessionCode::deactivate() { active_ = false; }
