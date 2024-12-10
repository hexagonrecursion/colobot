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

#include "object/subclass/base_alien.h"

#include <assert.h>
#include <utility>

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"
#include "object/object_create_params.h"
#include "object/motion/motionant.h"
#include "object/motion/motionbee.h"
#include "object/motion/motionqueen.h"
#include "object/motion/motionspider.h"
#include "object/motion/motionworm.h"
#include "physics/physics.h"
#include "object/motion/motion.h"
#include "object/old_object.h"


CBaseAlien::CBaseAlien(int id, ObjectType type)
    : CBaseVehicle(id, type),
      m_fixed(false)
{}

CBaseAlien::~CBaseAlien()
{}

std::unique_ptr<CBaseAlien> CBaseAlien::Create(
    const ObjectCreateParams& params,
    Gfx::COldModelManager* modelManager,
    Gfx::CEngine* engine)
{
    auto obj = std::make_unique<CBaseAlien>(params.id, params.type);

    obj->SetTeam(params.team);

    std::unique_ptr<CPhysics> physics = std::make_unique<CPhysics>(obj.get());

    std::unique_ptr<CMotion> motion;
    if ( params.type == OBJECT_MOTHER )
    {
        motion = std::make_unique<CMotionQueen>(obj.get());
    }
    if ( params.type == OBJECT_ANT )
    {
        motion = std::make_unique<CMotionAnt>(obj.get());
    }
    if ( params.type == OBJECT_SPIDER )
    {
        motion = std::make_unique<CMotionSpider>(obj.get());
    }
    if ( params.type == OBJECT_BEE )
    {
        motion = std::make_unique<CMotionBee>(obj.get());
    }
    if ( params.type == OBJECT_WORM )
    {
        motion = std::make_unique<CMotionWorm>(obj.get());
    }
    assert(motion != nullptr);

    physics->SetMotion(motion.get());
    motion->SetPhysics(physics.get());

    motion->Create(params.pos, params.angle, params.type, 0.0f, modelManager);

    obj->SetProgrammable();
    obj->SetMovable(std::move(motion), std::move(physics));

    return obj;
}

void CBaseAlien::SetFixed(bool fixed)
{
    m_fixed = fixed;
}

bool CBaseAlien::GetFixed()
{
    return m_fixed;
}

void CBaseAlien::Read(CLevelParserLine* line)
{
    COldObject::Read(line);

    SetFixed(line->GetParam("fixed")->AsBool(false));
}

void CBaseAlien::Write(CLevelParserLine* line)
{
    COldObject::Write(line);

    if (GetFixed())
        line->AddParam("fixed", std::make_unique<CLevelParserParam>(GetFixed()));
}
