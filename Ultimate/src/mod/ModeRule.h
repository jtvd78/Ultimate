#pragma once
#include <string>

class ModeRule {
public:
    explicit ModeRule(const std::string& name);
    explicit ModeRule(const std::string& name, bool enabled);

    void drawRule();

    bool m_enabled;

    const std::string m_name;
};
