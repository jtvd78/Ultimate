#include "LoadoutControl.h"
#include "settings/Settings.h"
#include "util/StringUtil.h"
#include <imgui/imgui.h>
#include <ultimate/Ultimate.h>

/**
* 
* Equipment:
* 
* frag_grenade_mp
* flare_mp
* semtex_mp
* throwingknife_mp
* claymore_mp
* c4_mp
* concussion_grenade_mp
* smoke_grenade_mp
* flash_grenade_mp
* 
* Note: Blast shield is a perk for some reason
* 
* 
*/

LoadoutControl::LoadoutControl()
    : m_replacementWeapon{ "fn2000" }
    , m_replacementPerk{ "speciality_null" }
    , m_genericRule{ "Generic" }
    , m_launchers{ "Launchers", WeaponClass::Launcher, { WeaponRule{ "m79" }, WeaponRule{ "rpg" }, WeaponRule{ "at4" }, WeaponRule{ "stinger" }, WeaponRule{ "javelin" } } }
    , m_handGuns{ "Handguns", WeaponClass::Handgun, { WeaponRule{ "beretta" }, WeaponRule{ "usp" }, WeaponRule{ "coltanaconda" }, WeaponRule{ "deserteagle" }, WeaponRule{ "deserteaglegold" } } }
    , m_machinePistols{ "Machine pistols", WeaponClass::MachinePistol, { WeaponRule{ "pp2000" }, WeaponRule{ "tmp" }, WeaponRule{ "glock" }, WeaponRule{ "beretta393" } } }
    , m_shotguns{ "Shotguns", WeaponClass::Shotgun, { WeaponRule{ "ranger" }, WeaponRule{ "model1887" }, WeaponRule{ "striker" }, WeaponRule{ "aa12" }, WeaponRule{ "m1014" }, WeaponRule{ "spas12" } } }
    , m_assaultRifles{ "Assault rifles", WeaponClass::AssaultRifle, { WeaponRule{ "ak47" }, WeaponRule{ "m16" }, WeaponRule{ "m4" }, WeaponRule{ "fn2000" }, WeaponRule{ "masada" }, WeaponRule{ "famas" }, WeaponRule{ "fal" }, WeaponRule{ "scar" }, WeaponRule{ "tavor" } } }
    , m_subMachineGuns{ "Sub machine guns", WeaponClass::SubMachineGun, { WeaponRule{ "mp5k" }, WeaponRule{ "uzi" }, WeaponRule{ "p90" }, WeaponRule{ "kriss" }, WeaponRule{ "ump45" } } }
    , m_lightMachineGuns{ "Light machine guns", WeaponClass::LightMachineGun, { WeaponRule{ "rpd" }, WeaponRule{ "sa80" }, WeaponRule{ "mg4" }, WeaponRule{ "m240" }, WeaponRule{ "aug" } } }
    , m_sniperRifles{ "Sniper rifles", WeaponClass::SniperRifle, { WeaponRule{ "barrett" }, WeaponRule{ "wa2000" }, WeaponRule{ "m21" }, WeaponRule{ "cheytac" } } }
    , m_special{ "Special", WeaponClass::Special, { WeaponRule{ "riotshield" } } }
    , m_custom{ CustomRule { "No Explosives" } }
    , m_modes{ ModeRule { "Interventions Only" } }
    , m_perks{
          PerkRule{ "specialty_marathon" },
          PerkRule{ "specialty_fastreload" },
          PerkRule{ "specialty_scavenger" },
          PerkRule{ "specialty_onemanarmy" },
          PerkRule{ "specialty_bling" },
          PerkRule{ "specialty_bulletdamage" },
          PerkRule{ "specialty_lightweight" },
          PerkRule{ "specialty_hardline" },
          PerkRule{ "specialty_coldblooded" },
          PerkRule{ "specialty_explosivedamage" },
          PerkRule{ "specialty_extendedmelee" },
          PerkRule{ "specialty_bulletaccuracy" },
          PerkRule{ "specialty_localjammer" },
          PerkRule{ "specialty_heartbreaker" },
          PerkRule{ "specialty_pistoldeath" },
          PerkRule{ "specialty_delaymine" },
          PerkRule{ "specialty_selectivehearing" },
          PerkRule{ "specialty_quickdraw" },
          PerkRule{ "specialty_fastsprintrecovery" },
          PerkRule{ "specialty_secondarybling" },
          PerkRule{ "specialty_gpsjammer" },
          PerkRule{ "specialty_fastmantle" },
          PerkRule{ "specialty_armorpiercing" },
          PerkRule{ "specialty_rollover" },
          PerkRule{ "specialty_omaquickchange" },
          PerkRule{ "specialty_extraammo" },
          PerkRule{ "specialty_spygame" },
          PerkRule{ "specialty_holdbreath" },
          PerkRule{ "specialty_laststandoffhand" },
          PerkRule{ "specialty_quieter" },
          PerkRule{ "specialty_dangerclose" },
          PerkRule{ "specialty_falldamage" }
      }
    , m_deathStreaks{ PerkRule{ "specialty_grenadepulldeath" }, PerkRule{ "specialty_c4death" }, PerkRule{ "specialty_combathigh" }, PerkRule{ "specialty_finalstand" }, PerkRule{ "specialty_copycat" } }
{
}

void LoadoutControl::drawLoadoutControls()
{
    ImGui::Begin("Loadout", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::TreeNode("Attachments")) {
        for (auto& rule : m_genericRule.m_attachments) {
            rule.drawAttachmentRule();
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Weapons")) {
        m_launchers.drawWeaponClassRule();
        m_handGuns.drawWeaponClassRule();
        m_machinePistols.drawWeaponClassRule();
        m_shotguns.drawWeaponClassRule();
        m_assaultRifles.drawWeaponClassRule();
        m_subMachineGuns.drawWeaponClassRule();
        m_lightMachineGuns.drawWeaponClassRule();
        m_sniperRifles.drawWeaponClassRule();
        m_special.drawWeaponClassRule();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Perks")) {

        if (ImGui::TreeNode("Specialties")) {
            for (auto& rule : m_perks) {
                rule.drawPerkRule();
            }

            ImGui::TreePop();
        }

//        if (ImGui::TreeNode("Death streaks")) {
//            for (auto& rule : m_deathStreaks) {
//                rule.drawPerkRule();
//            }
//
//            ImGui::TreePop();
//        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Modes")) {
        for (auto& rule : m_modes) {
            rule.drawRule();
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Custom")) {
        for (auto& rule : m_custom) {
            rule.drawRule();
        }

        ImGui::TreePop();
    }

    ImGui::End();
}

std::string LoadoutControl::setSpawnWeapon(const std::string& initialWeapon)
{
    if (findMode("Interventions Only")->m_enabled) {
        return "cheytac_mp";
    }
    
    // Default Behavior
    if (shouldWeaponBeReplaced(initialWeapon)) 
    {
        return m_replacementWeapon.build();
    }
    else
    {
        return initialWeapon;
    }   
}

std::string LoadoutControl::giveWeapon(const std::string& initialWeapon)
{
    const auto index = BG_FindWeaponIndexForName(initialWeapon.c_str());
    if (findMode("Interventions Only")->m_enabled) {
        if (IsWeapon(index)) {
            return "cheytac_mp";
        }
        else if (IsEquipment(index)) {
            return "throwingknife_mp";
        }
    }
    
    // Default behavior.
    if (shouldWeaponBeReplaced(initialWeapon))
    {
        return m_replacementWeapon.build();
    }
    else
    {
        return initialWeapon;
    }   
}

template<std::size_t SIZE>
bool contains(const std::string needle, const std::array<std::string, SIZE> haystack) {
    const std::string* found = std::find(std::begin(haystack), std::end(haystack), needle);

    return found != std::end(haystack)
}

PerkCategory getPerkNumber(const std::string& perkName) {
    const std::array<std::string, 5> perk1 = {
        "specialty_marathon",
        "specialty_fastreload",
        "specialty_scavenger",
        "specialty_bling",
        "specialty_onemanarmy"
    };

    const std::array<std::string, 5> perk2 = {
        "specialty_bulletdamage",
        "specialty_lightweight",
        "specialty_hardline",
        "specialty_coldblooded",
        "specialty_explosivedamage"
    };

    const std::array<std::string, 6> perk3 = {
        "specialty_extendedmelee",
        "specialty_bulletaccuracy",
        "specialty_localjammer",
        "specialty_heartbreaker",
        "specialty_detectexplosive",
        "specialty_pistoldeath"
    };

    const std::array<std::string, 5> perk1pros = {
       "specialty_fastmantle",
       "specialty_quickdraw",
       "specialty_extraammo",
       "specialty_secondarybling",
       "specialty_omaquickchange"
    };

    const std::array<std::string, 5> perk2pros = {
        "specialty_armorpiercing",
        "specialty_fastsprintrecovery",
        "specialty_rollover",
        "specialty_spygame",
        "specialty_dangerclose"
    };

    const std::array<std::string, 6> perk3pros = {
        "specialty_falldamage",
        "specialty_holdbreath",
        "specialty_delaymine",
        "specialty_quieter",
        "specialty_selectivehearing",
        "specialty_laststandoffhand"
    };

    if (contains(perkName, perk1)) {
        return PERK1;
    }

    if (contains(perkName, perk2)) {
        return PERK2;
    }

    if (contains(perkName, perk3)) {
        return PERK3;
    }

    if (contains(perkName, perk1pros)) {
        return PERK1PRO;
    }
    
    if (contains(perkName, perk2pros)) {
        return PERK2PRO;
    }

    if (contains(perkName, perk3pros)) {
        return PERK3PRO;
    }

    return OTHER;
}


std::string LoadoutControl::givePerk(const std::string& perkName) {
    if (findMode("Interventions Only")->m_enabled) {
        if (perkName == "_specialty_blastshield" || perkName == "specialty_blastshield") {
            return "speciality_null";
        }

        const auto setPerk1 = "specialty_fastreload";
        const auto setPerk1Pro = "specialty_quickdraw";
        const auto setPerk2 = "specialty_bulletdamage";
        const auto setPerk2Pro = "specialty_armorpiercing";
        const auto setPerk3 = "specialty_extendedmelee";
        const auto setPerk3Pro = "specialty_falldamage";

        switch (getPerkNumber(perkName)) {
        case PERK1:
            return setPerk1;
        case PERK2:
            return setPerk2;
        case PERK3:
            return setPerk3;
        case PERK1PRO:
            return setPerk1Pro;
        case PERK2PRO:
            return setPerk2Pro;
        case PERK3PRO:
            return setPerk3Pro;
        default:
            return perkName;
        }

        // Default behavior.
        if (shouldPerkBeReplaced(perkName))
        {
            return m_replacementPerk;
        }
        else
        {
            return perkName;
        }

    }
}

bool LoadoutControl::shouldWeaponBeReplaced(const std::string& weapon)
{
    auto parts = breakdownWeapon(weapon);

    const auto rule = findWeapon(parts.m_weapon);

    if (rule == nullptr) {
        return false;
    }

    if (!rule->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying weapon %s due to weapon %s being banned\n", weapon.c_str(), rule->m_name.c_str());
        }
        return true;
    }

    const auto genericAttachment1 = m_genericRule.findAttachment(parts.m_firstAttachment);
    if (genericAttachment1 != nullptr && !genericAttachment1->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying weapon %s due to attachment %s being globally banned\n", weapon.c_str(), parts.m_firstAttachment.c_str());
        }
        return true;
    }

    const auto genericAttachment2 = m_genericRule.findAttachment(parts.m_secondAttachment);
    if (genericAttachment2 != nullptr && !genericAttachment2->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying weapon %s due to attachment %s being globally banned\n", weapon.c_str(), parts.m_secondAttachment.c_str());
        }
        return true;
    }

    const auto attachment1 = rule->findAttachment(parts.m_firstAttachment);
    if (attachment1 != nullptr && !attachment1->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying weapon %s due to attachment %s being banned\n", weapon.c_str(), parts.m_firstAttachment.c_str());
        }
        return true;
    }

    const auto attachment2 = rule->findAttachment(parts.m_secondAttachment);
    if (attachment2 != nullptr && !attachment2->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying weapon %s due to attachment %s being banned\n", weapon.c_str(), parts.m_secondAttachment.c_str());
        }
        return true;
    }

    return false;
}

bool LoadoutControl::shouldPerkBeReplaced(const std::string& perk)
{
    const auto rule = findSpeciality(perk);

    if (rule == nullptr) {
        return false;
    }

    if (!rule->m_allowed) {
        if (g_settings.m_logSettings.m_logLoadoutControl) {
            std::printf("Denying perk %s due to perk %s being banned\n", perk.c_str(), rule->m_name.c_str());
        }
        return true;
    }

    return false;
}

const PerkRule* LoadoutControl::findSpeciality(const std::string& perk)
{
    if (const auto result = findPerk(perk); result != nullptr) {
        return result;
    }
    if (const auto result = findDeathStreak(perk); result != nullptr) {
        return result;
    }
    return nullptr;
}

const WeaponRule* LoadoutControl::findWeapon(const std::string& weapon)
{
    if (const auto result = findLauncher(weapon); result != nullptr) {
        return result;
    }
	if (const auto result = findHandgun(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findMachinePistol(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findShotgun(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findAssaultRifle(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findSubMachineGun(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findLightMachineGun(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findSniperRifle(weapon); result != nullptr) {
		return result;
	}
	if (const auto result = findSpecial(weapon); result != nullptr) {
		return result;
	}
	return nullptr;
}

const PerkRule* LoadoutControl::findPerk(const std::string& perk)
{
    return findSpeciality(&m_perks.begin(), &m_perks.end(), perk);
}

const PerkRule* LoadoutControl::findDeathStreak(const std::string& perk)
{
    return findSpeciality(&m_deathStreaks.begin(), &m_deathStreaks.end(), perk);
}

const WeaponRule* LoadoutControl::findLauncher(const std::string& weapon)
{
    return findWeapon(&m_launchers.m_rules.begin(), &m_launchers.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findHandgun(const std::string& weapon)
{
    return findWeapon(&m_handGuns.m_rules.begin(), &m_handGuns.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findMachinePistol(const std::string& weapon)
{
    return findWeapon(&m_machinePistols.m_rules.begin(), &m_machinePistols.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findShotgun(const std::string& weapon)
{
    return findWeapon(&m_shotguns.m_rules.begin(), &m_shotguns.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findAssaultRifle(const std::string& weapon)
{
    return findWeapon(&m_assaultRifles.m_rules.begin(), &m_assaultRifles.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findSubMachineGun(const std::string& weapon)
{
    return findWeapon(&m_subMachineGuns.m_rules.begin(), &m_subMachineGuns.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findLightMachineGun(const std::string& weapon)
{
    return findWeapon(&m_lightMachineGuns.m_rules.begin(), &m_lightMachineGuns.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findSniperRifle(const std::string& weapon)
{
    return findWeapon(&m_sniperRifles.m_rules.begin(), &m_sniperRifles.m_rules.end(), weapon);
}

const WeaponRule* LoadoutControl::findSpecial(const std::string& weapon)
{
    return findWeapon(&m_special.m_rules.begin(), &m_special.m_rules.end(), weapon);
}

WeaponParts LoadoutControl::breakdownWeapon(const std::string& weapon) const
{
    auto parts = StringSplit(weapon, '_');

	const auto size = parts.size();
    if (size > 3) {
        return { parts[0], parts[1], parts[2] };
    }
	if (size > 2) {
		return { parts[0], parts[1] };
	}
	if (size > 1) {
		return { parts[0] };
	}
	return {};
}

std::string WeaponParts::build() const
{
    std::string out;

    if (!m_weapon.empty()) {
        out += m_weapon;
    }

    if (!m_firstAttachment.empty()) {
        out += std::string("_");
        out += m_firstAttachment;
    }

    if (!m_secondAttachment.empty()) {
        out += std::string("_");
        out += m_secondAttachment;
    }

    out += "_mp";

    return out;
}

ModeRule* LoadoutControl::findMode(std::string modeName) {
    for (auto& mode : m_modes) {
        if (mode.m_name == modeName) {
            return &mode;
        }
    }

    return nullptr;
}