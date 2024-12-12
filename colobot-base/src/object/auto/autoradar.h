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

#include "object/auto/auto.h"
#include "common/error.h"

class COldObject;
struct Event;



enum AutoRadarPhase
{
    ARAP_WAIT       = 1,    // waiting
    ARAP_SEARCH     = 2,    // seeking
    ARAP_SHOW       = 3,    // watching
    ARAP_SINUS      = 4,    // oscillates
};



class CAutoRadar : public CAuto
{
public:
    CAutoRadar(COldObject* object);
    ~CAutoRadar();

    void        DeleteObject(bool bAll=false) override;

    void        Init() override;
    bool        EventProcess(const Event &event) override;
    bool        CreateInterface(bool bSelect) override;
    Error       GetError() override;

protected:
    void        UpdateInterface();
    bool        SearchEnemy(glm::vec3 &pos);

protected:
    AutoRadarPhase  m_phase = ARAP_WAIT;
    float           m_progress = 0.0f;
    float           m_speed = 0.0f;
    float           m_aTime = 0.0f;
    float           m_timeVirus = 0.0f;
    float           m_lastParticle =0.0f;
    float           m_angle = 0.0f;
    float           m_start = 0.0f;
    int             m_totalDetect = 0;
};
