//################################################################################################################################
// PrusaSlicer development only -> !!!TO BE REMOVED!!!
#include "libslic3r/Technologies.hpp"
//################################################################################################################################

///|/ Copyright (c) Prusa Research 2023 Enrico Turri @enricoturri1966
///|/
///|/ libvgcode is released under the terms of the AGPLv3 or higher
///|/
#include "ExtrusionRoles.hpp"

//################################################################################################################################
// PrusaSlicer development only -> !!!TO BE REMOVED!!!
#if ENABLE_NEW_GCODE_VIEWER
//################################################################################################################################

namespace libvgcode {

void ExtrusionRoles::add(EGCodeExtrusionRole role, const std::array<float, static_cast<size_t>(ETimeMode::COUNT)>& times)
{
    auto role_it = m_items.find(role);
    if (role_it == m_items.end())
        role_it = m_items.insert(std::make_pair(role, Item())).first;

    for (size_t i = 0; i < static_cast<size_t>(ETimeMode::COUNT); ++i) {
        role_it->second.times[i] += times[i];
    }
}

uint32_t ExtrusionRoles::get_roles_count() const
{
    return static_cast<uint32_t>(m_items.size());
}

std::vector<EGCodeExtrusionRole> ExtrusionRoles::get_roles() const
{
    std::vector<EGCodeExtrusionRole> ret;
    ret.reserve(m_items.size());
    for (const auto& [role, item] : m_items) {
        ret.emplace_back(role);
    }
    return ret;
}

float ExtrusionRoles::get_time(EGCodeExtrusionRole role, ETimeMode mode) const
{
    const auto role_it = m_items.find(role);
    if (role_it == m_items.end())
        return 0.0f;

    return (mode < ETimeMode::COUNT) ? role_it->second.times[static_cast<size_t>(mode)] : 0.0f;
}

void ExtrusionRoles::reset()
{
    m_items.clear();
}

} // namespace libvgcode

//################################################################################################################################
// PrusaSlicer development only -> !!!TO BE REMOVED!!!
#endif // ENABLE_NEW_GCODE_VIEWER
//################################################################################################################################
