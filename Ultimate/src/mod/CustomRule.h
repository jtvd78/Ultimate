#pragma once
#include <string>

class CustomRule {
public:
    explicit CustomRule(const std::string& name);

    void drawRule();

    bool m_enabled;

    const std::string m_name;
};
