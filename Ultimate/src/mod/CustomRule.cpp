#include "CustomRule.h"
#include <imgui/imgui.h>

CustomRule::CustomRule(const std::string& name) : m_name(name) {}

void CustomRule::drawRule()
{
    ImGui::Checkbox(m_name.c_str(), &m_enabled);
}
