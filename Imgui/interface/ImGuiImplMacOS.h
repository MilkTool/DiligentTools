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

#include <mutex>
#include "ImGuiImplDiligent.h"

@class NSEvent;
@class NSView;

namespace Diligent
{

class ImGuiImplMacOS final : public ImGuiImplDiligent
{
public:
    ImGuiImplMacOS(IRenderDevice*  _Nonnull pDevice,
                   TEXTURE_FORMAT  BackBufferFmt,
                   TEXTURE_FORMAT  DepthBufferFmt,
                   Uint32          DisplayWidth,
                   Uint32          DisplayHeight,
                   Uint32          InitialVertexBufferSize = ImGuiImplDiligent::DefaultInitialVBSize,
                   Uint32          InitialIndexBufferSize  = ImGuiImplDiligent::DefaultInitialIBSize);
    ~ImGuiImplMacOS();

    // clang-format off
    ImGuiImplMacOS             (const ImGuiImplMacOS&)  = delete;
    ImGuiImplMacOS             (      ImGuiImplMacOS&&) = delete;
    ImGuiImplMacOS& operator = (const ImGuiImplMacOS&)  = delete;
    ImGuiImplMacOS& operator = (      ImGuiImplMacOS&&) = delete;
    // clang-format on

    virtual void NewFrame()override final;
    virtual void Render(IDeviceContext* _Nonnull pCtx)override final;
    bool HandleOSXEvent(NSEvent* _Nonnull event, NSView* _Nonnull view);
    void SetDisplaySize(Uint32 DisplayWidth, Uint32 DisplayHeight);

private:
    std::mutex m_Mtx;
};

}
