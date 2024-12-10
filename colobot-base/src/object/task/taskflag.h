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

#include "object/task/task.h"
#include "object/object_type.h"
#include "common/error.h"

class CObject;
class COldObject;
struct Event;

enum TaskFlagOrder
{
    TFL_CREATE  = 0,    // sets
    TFL_DELETE  = 1,    // removes
};



class CTaskFlag : public CForegroundTask
{
public:
    CTaskFlag(COldObject* object);
    ~CTaskFlag();

    bool        EventProcess(const Event &event) override;

    Error       Start(TaskFlagOrder order, int rank);
    Error       IsEnded() override;
    bool        Abort() override;

protected:
    Error       CreateFlag(int rank);
    Error       DeleteFlag();
    CObject*    SearchNearest(glm::vec3 pos, ObjectType type);
    int         CountObject(ObjectType type);

protected:
    TaskFlagOrder   m_order = TFL_CREATE;
    float           m_time = 0.0f;
    bool            m_bError = false;
};
