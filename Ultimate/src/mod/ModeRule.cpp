#include "ModeRule.h"
#include <imgui/imgui.h>

ModeRule::ModeRule(const std::string& name, bool enabled) : m_name(name), m_enabled(enabled) {}

ModeRule::ModeRule(const std::string& name) : m_name(name), m_enabled(false) {}

void ModeRule::drawRule()
{
    ImGui::Checkbox(m_name.c_str(), &m_enabled);
}
