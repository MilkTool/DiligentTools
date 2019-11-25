/*     Copyright 2019 Diligent Graphics LLC
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#pragma once

#include <algorithm>
#include <limits>

#include "../../ThirdParty/imgui/imgui.h"
#include "../../ThirdParty/imgui/imgui_internal.h"

namespace Diligent
{

class ImGuiScopedDisabler
{
public:
    explicit ImGuiScopedDisabler(bool Disable, float AlphaScale = 0.25f) :
        m_IsDisabled{Disable}
    {
        if (m_IsDisabled)
        {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * AlphaScale);
        }
    }

    ~ImGuiScopedDisabler()
    {
        if (m_IsDisabled)
        {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }
    }

private:
    const bool m_IsDisabled;
};

} // namespace Diligent

namespace ImGui
{

template <typename T>
inline bool Checkbox(const char* label, T* v)
{
    bool b = *v != 0;

    auto pressed = Checkbox(label, &b);
    if (pressed)
        *v = b ? 1 : 0;
    return pressed;
}

inline void HelpMarker(const char* desc, bool IsSameLine = true, const char* marker = "(?)")
{
    if (IsSameLine)
        SameLine();

    TextDisabled("%s", marker);
    if (IsItemHovered())
    {
        BeginTooltip();
        PushTextWrapPos(GetFontSize() * 35.0f);
        TextUnformatted(desc);
        PopTextWrapPos();
        EndTooltip();
    }
}

template <typename T, typename = typename std::enable_if<std::numeric_limits<T>::is_integer>::type>
bool SliderIntT(const char* label, T* v, int v_min, int v_max, const char* format = "%d")
{
    int i = static_cast<int>(*v);

    auto value_changed = ImGui::SliderInt(label, &i, v_min, v_max, format);
    if (value_changed)
        *v = static_cast<T>(i);
    return value_changed;
}

template <typename T>
bool Combo(const char* label, T* current_item, const std::pair<T, const char*> items[], int items_count, int popup_max_height_in_items = -1)
{
    int item_idx = 0;
    while (item_idx < items_count && items[item_idx].first != *current_item)
        ++item_idx;
    if (item_idx >= items_count)
    {
        UNEXPECTED("Current item was not found in the items list");
        return false;
    }
    std::vector<const char*> names(items_count);
    for (int i = 0; i < items_count; ++i)
        names[i] = items[i].second;
    auto value_changed = Combo(label, &item_idx, names.data(), items_count, popup_max_height_in_items);
    if (value_changed)
        *current_item = items[item_idx].first;

    return value_changed;
}

} // namespace ImGui
