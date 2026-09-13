#ifndef MEMBER2_SESSION_CODE_H
#define MEMBER2_SESSION_CODE_H

#include <string>

class SessionCode {
public:
    void generate();
    bool validate(const std::string& enteredCode) const;
    const std::string& value() const;
    void deactivate();

private:
    std::string code_;
    bool active_ = false;
};

#endif
