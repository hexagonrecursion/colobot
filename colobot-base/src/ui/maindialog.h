/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2023, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <string>

#include "common/restext.h"

class CSettings;
class CSoundInterface;
class CRobotMain;
struct Event;

namespace Gfx
{
class CEngine;
class CParticle;
} // namespace Gfx

namespace Ui
{

class CInterface;

class CMainDialog
{
public:
    CMainDialog();
    ~CMainDialog();

    bool    EventProcess(const Event &event);


    using DialogCallback = std::function<void()>;
    void    StartQuestion(const std::string& text,
                          bool warningYes = false, bool warningNo = false,
                          bool fireParticles = false,
                          DialogCallback yes = nullptr, DialogCallback no = nullptr);
    void    StartQuestion(ResTextType text,
                          bool warningYes = false, bool warningNo = false,
                          bool fireParticles = false,
                          DialogCallback yes = nullptr, DialogCallback no = nullptr);
    void    StartInformation(const std::string& title,
                             const std::string& text,
                             const std::string& details,
                             bool warning = false,
                             bool fireParticles = false,
                             DialogCallback ok = nullptr);
    void    StartPauseMenu();
    void    StopDialog();
    bool    IsDialog();

protected:
    void    StartDialog(const glm::vec2& dim, bool fireParticles);
    void    FrameDialog(float rTime);

protected:
    CRobotMain*       m_main;
    Gfx::CEngine*     m_engine;
    Gfx::CParticle*   m_particle;
    CInterface*       m_interface;
    CSoundInterface*  m_sound;
    CSettings*        m_settings;

    enum class DialogType
    {
        Question,
        PauseMenu
    };

    bool                 m_dialogOpen;
    DialogType           m_dialogType;
    bool                 m_dialogFireParticles;
    glm::vec2            m_dialogPos;
    glm::vec2            m_dialogDim;
    float                m_dialogTime;
    float                m_dialogParti;

    DialogCallback       m_callbackYes;
    DialogCallback       m_callbackNo;
};

} // namespace Ui
