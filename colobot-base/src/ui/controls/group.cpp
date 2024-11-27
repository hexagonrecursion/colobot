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


#include "ui/controls/group.h"

#include <filesystem>
#include <string>

#include "common/event.h"
#include "graphics/core/renderers.h"
#include "graphics/core/transparency.h"
#include "graphics/engine/engine.h"
#include "math/func.h"
#include "graphics/core/texture.h"


namespace Ui
{
// Object's constructor.

CGroup::CGroup() : CControl()
{
}

// Object's destructor.

CGroup::~CGroup()
{
}


// Creates a new button.

bool CGroup::Create(const glm::vec2& pos, const glm::vec2& dim, int icon, EventType eventType)
{
    if ( eventType == EVENT_NULL )  eventType = GetUniqueEventType();

    CControl::Create(pos, dim, icon, eventType);

    if ( icon == -1 )
    {
        std::string name = GetResourceName(eventType);
        SetName(name);
    }

    return true;
}


// Management of an event.

bool CGroup::EventProcess(const Event &event)
{
    return true;
}


// Draw button.

void CGroup::Draw()
{
    glm::vec2   uv1,uv2, corner, pos, dim;
    float       dp;
    int         icon;

    if ( (m_state & STATE_VISIBLE) == 0 )  return;

    if ( m_state & STATE_SHADOW )
    {
        DrawShadow(m_pos, m_dim);
    }

    dp = 0.5f / 256.0f;

    auto renderer = m_engine->GetUIRenderer();

    if ( m_icon == 0 )  // hollow frame?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);

        uv1.x = 160.0f / 256.0f;
        uv1.y = 192.0f / 256.0f;  // u-v texture
        uv2.x = 192.0f / 256.0f;
        uv2.y = 224.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 10.0f/640.0f;
        corner.y = 10.0f/480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 8.0f/256.0f);
    }
    if ( m_icon == 1 )  // orange solid opaque?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);

        uv1.x = 104.0f / 256.0f;
        uv1.y =  48.0f / 256.0f;
        uv2.x = 112.0f / 256.0f;
        uv2.y =  64.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 2 )  // orange degrade -> transparent?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);

        uv1.x = 112.0f / 256.0f;
        uv1.y =  48.0f / 256.0f;
        uv2.x = 120.0f / 256.0f;
        uv2.y =  64.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 3 )  // transparent gradient -> gray?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);

        uv1.x = 120.0f / 256.0f;
        uv1.y =  48.0f / 256.0f;
        uv2.x = 128.0f / 256.0f;
        uv2.y =  64.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 4 )  // degrade blue corner?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);

        uv1.x = 192.0f / 256.0f;
        uv1.y = 128.0f / 256.0f;
        uv2.x = 224.0f / 256.0f;
        uv2.y = 160.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 5 )  // degrade orange corner?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);

        uv1.x = 224.0f / 256.0f;
        uv1.y = 128.0f / 256.0f;
        uv2.x = 256.0f / 256.0f;
        uv2.y = 160.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 6 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);

        uv1.x =   0.0f / 256.0f;  // brown transparent
        uv1.y =  75.0f / 256.0f;
        uv2.x =  64.0f / 256.0f;
        uv2.y = 128.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 4.0f / 640.0f;
        corner.y = 4.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 8.0f/256.0f);
    }
    if ( m_icon == 7 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button1.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);

        uv1.x =  64.0f / 256.0f;
        uv1.y =   0.0f / 256.0f;
        uv2.x =  96.0f / 256.0f;
        uv2.y =  32.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2, 8.0f/256.0f);
    }
    if ( m_icon == 8 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);

        uv1.x =  64.0f / 256.0f;  // green transparent
        uv1.y = 160.0f / 256.0f;
        uv2.x = 160.0f / 256.0f;
        uv2.y = 176.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2, 8.0f/256.0f);
    }
    if ( m_icon == 9 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);

        uv1.x =  64.0f / 256.0f;  // red transparent
        uv1.y = 176.0f/256.0f;
        uv2.x = 160.0f/256.0f;
        uv2.y = 192.0f/256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2, 8.0f/256.0f);
    }
    if ( m_icon == 10 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);

        uv1.x =  64.0f / 256.0f;  // blue transparent
        uv1.y = 192.0f / 256.0f;
        uv2.x = 160.0f / 256.0f;
        uv2.y = 208.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2, 8.0f/256.0f);
    }
    if ( m_icon == 11 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        uv1.x =  64.0f / 256.0f;  // yellow transparent
        uv1.y = 224.0f / 256.0f;
        uv2.x = 160.0f / 256.0f;
        uv2.y = 240.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2, 8.0f/256.0f);
    }
    if ( m_icon == 12 )  // viewfinder cross?
    {
        dim.x = m_dim.x / 2.0f;
        dim.y = m_dim.y / 2.0f;

        auto texture = m_engine->LoadTexture("textures/interface/mouse.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x = m_pos.x-m_dim.x/300.0f;
        pos.y = m_pos.y+m_dim.y/300.0f+dim.y;
        uv1.x =   0.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv2.x =  63.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, dim, uv1, uv2);  // ul
        pos.x += dim.x;
        Math::Swap(uv1.x, uv2.x);
        DrawIcon(pos, dim, uv1, uv2);  // ur
        pos.y -= dim.y;
        Math::Swap(uv1.y, uv2.y);
        DrawIcon(pos, dim, uv1, uv2);  // dr
        pos.x -= dim.x;
        Math::Swap(uv1.x, uv2.x);
        DrawIcon(pos, dim, uv1, uv2);  // dl

        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        pos.x = m_pos.x+m_dim.x/300.0f;
        pos.y = m_pos.y-m_dim.y/300.0f+dim.y;
        uv1.x =  64.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv2.x = 127.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, dim, uv1, uv2);  // ul
        pos.x += dim.x;
        Math::Swap(uv1.x, uv2.x);
        DrawIcon(pos, dim, uv1, uv2);  // ur
        pos.y -= dim.y;
        Math::Swap(uv1.y, uv2.y);
        DrawIcon(pos, dim, uv1, uv2);  // dr
        pos.x -= dim.x;
        Math::Swap(uv1.x, uv2.x);
        DrawIcon(pos, dim, uv1, uv2);  // dl
    }
    if ( m_icon == 13 )  // corner upper / left?
    {
        auto texture = m_engine->LoadTexture("textures/interface/mouse.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x = m_pos.x-m_dim.x/150.0f;
        pos.y = m_pos.y+m_dim.y/150.0f;
        uv1.x = 128.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv2.x = 191.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        pos.x = m_pos.x+m_dim.x/150.0f;
        pos.y = m_pos.y-m_dim.y/150.0f;
        uv1.x = 192.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv2.x = 255.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 14 )  // corner upper / right?
    {
        auto texture = m_engine->LoadTexture("textures/interface/mouse.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x = m_pos.x-m_dim.x/150.0f;
        pos.y = m_pos.y+m_dim.y/150.0f;
        uv2.x = 128.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv1.x = 191.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        pos.x = m_pos.x+m_dim.x/150.0f;
        pos.y = m_pos.y-m_dim.y/150.0f;
        uv2.x = 192.5f / 256.0f;
        uv1.y = 192.5f / 256.0f;
        uv1.x = 255.5f / 256.0f;
        uv2.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 15 )  // corner lower / left?
    {
        auto texture = m_engine->LoadTexture("textures/interface/mouse.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x = m_pos.x-m_dim.x/150.0f;
        pos.y = m_pos.y+m_dim.y/150.0f;
        uv1.x = 128.5f / 256.0f;
        uv2.y = 192.5f / 256.0f;
        uv2.x = 191.5f / 256.0f;
        uv1.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        pos.x = m_pos.x+m_dim.x/150.0f;
        pos.y = m_pos.y-m_dim.y/150.0f;
        uv1.x = 192.5f / 256.0f;
        uv2.y = 192.5f / 256.0f;
        uv2.x = 255.5f / 256.0f;
        uv1.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 16 )  // corner lower / left?
    {
        auto texture = m_engine->LoadTexture("textures/interface/mouse.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x = m_pos.x-m_dim.x/150.0f;
        pos.y = m_pos.y+m_dim.y/150.0f;
        uv2.x = 128.5f / 256.0f;
        uv2.y = 192.5f / 256.0f;
        uv1.x = 191.5f / 256.0f;
        uv1.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        pos.x = m_pos.x+m_dim.x/150.0f;
        pos.y = m_pos.y-m_dim.y/150.0f;
        uv2.x = 192.5f / 256.0f;
        uv2.y = 192.5f / 256.0f;
        uv1.x = 255.5f / 256.0f;
        uv1.y = 255.5f / 256.0f;
        DrawIcon(pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 17 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =   0.0f / 256.0f;  // blue frame
        uv1.y =  75.0f / 256.0f;
        uv2.x =  64.0f / 256.0f;
        uv2.y = 128.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 6.0f / 640.0f;
        corner.y = 6.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 2.0f/256.0f);
    }
    if ( m_icon == 18 )  // arrow> for SatCom?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button1.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        uv1.x =   0.0f / 256.0f;   // >
        uv1.y = 192.0f / 256.0f;
        uv2.x =  32.0f / 256.0f;
        uv2.y = 224.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 19 )  // SatCom symbol?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button1.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        uv1.x = 224.0f / 256.0f;  // SatCom symbol
        uv1.y = 224.0f / 256.0f;
        uv2.x = 256.0f / 256.0f;
        uv2.y = 256.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 20 )  // solid blue background?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button1.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        uv1.x = 224.0f / 256.0f;
        uv1.y =  32.0f / 256.0f;
        uv2.x = 256.0f / 256.0f;
        uv2.y =  64.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 21 )  // stand-by symbol?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::WHITE);
        uv1.x = 160.0f / 256.0f;
        uv1.y =  32.0f / 256.0f;
        uv2.x = 192.0f / 256.0f;
        uv2.y =  64.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }
    if ( m_icon == 22 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  64.0f / 256.0f;  // opaque yellow
        uv1.y = 224.0f / 256.0f;
        uv2.x = 160.0f / 256.0f;
        uv2.y = 240.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 5.0f / 640.0f;
        corner.y = 5.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 3.0f/256.0f);
    }

    if ( m_icon == 23 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  64.0f / 256.0f;  // yellow
        uv1.y = 192.0f / 256.0f;
        uv2.x =  80.0f / 256.0f;
        uv2.y = 208.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 4.0f / 640.0f;
        corner.y = 4.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 2.0f/256.0f);
    }
    if ( m_icon == 24 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  80.0f / 256.0f;  // orange
        uv1.y = 192.0f / 256.0f;
        uv2.x =  96.0f / 256.0f;
        uv2.y = 208.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 4.0f / 640.0f;
        corner.y = 4.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 2.0f/256.0f);
    }
    if ( m_icon == 25 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  64.0f / 256.0f;  // orange
        uv1.y = 208.0f / 256.0f;
        uv2.x =  80.0f / 256.0f;
        uv2.y = 224.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 4.0f / 640.0f;
        corner.y = 4.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 2.0f/256.0f);
    }
    if ( m_icon == 26 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  80.0f / 256.0f;   // red
        uv1.y = 208.0f / 256.0f;
        uv2.x =  96.0f / 256.0f;
        uv2.y = 224.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        corner.x = 4.0f / 640.0f;
        corner.y = 4.0f / 480.0f;
        DrawIcon(m_pos, m_dim, uv1, uv2, corner, 2.0f/256.0f);
    }
    if ( m_icon == 27 )
    {
        auto texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        uv1.x =  32.0f / 256.0f;
        uv1.y =   0.0f / 256.0f;
        uv2.x =  64.0f / 256.0f;
        uv2.y =  32.0f / 256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(m_pos, m_dim, uv1, uv2);
    }

    if ( m_icon >= 100 && m_icon <= 120 )  // building?
    {
        auto texture = m_engine->LoadTexture("textures/interface/button2.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        pos = m_pos;
        dim = m_dim;
        uv1.x = 32.0f / 256.0f;
        uv1.y = 32.0f / 256.0f;
        uv2.x = uv1.x+32.0f/256.0f;
        uv2.y = uv1.y+32.0f/256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(pos, dim, uv1, uv2);

        texture = m_engine->LoadTexture("textures/interface/button3.png");
        renderer->SetTexture(texture);
        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        pos.x +=  8.0f / 640.0f;
        pos.y +=  8.0f / 480.0f;
        dim.x -= 16.0f / 640.0f;
        dim.y -= 16.0f / 480.0f;
        uv1.x = 32.0f / 256.0f;
        uv1.y =  0.0f / 256.0f;
        uv2.x = uv1.x+32.0f/256.0f;
        uv2.y = uv1.y+32.0f/256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(pos, dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::NONE);
        pos.x += 2.0f / 640.0f;
        pos.y += 2.0f / 480.0f;
        dim.x -= 4.0f / 640.0f;
        dim.y -= 4.0f / 480.0f;
        uv1.x = 0.0f / 256.0f;
        uv1.y = 0.0f / 256.0f;
        uv2.x = uv1.x+32.0f/256.0f;
        uv2.y = uv1.y+32.0f/256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(pos, dim, uv1, uv2);

        renderer->SetTransparency(Gfx::TransparencyMode::BLACK);
        pos.x +=  8.0f / 640.0f;
        pos.y +=  8.0f / 480.0f;
        dim.x -= 16.0f / 640.0f;
        dim.y -= 16.0f / 480.0f;
        if ( m_icon == 100 )  icon = 43;  // base ?
        if ( m_icon == 101 )  icon = 32;  // factory ?
        if ( m_icon == 102 )  icon = 35;  // research ?
        if ( m_icon == 103 )  icon = 34;  // convert ?
        if ( m_icon == 104 )  icon = 36;  // station ?
        if ( m_icon == 105 )  icon = 40;  // radar ?
        if ( m_icon == 106 )  icon = 41;  // repair ?
        if ( m_icon == 107 )  icon = 37;  // tower ?
        if ( m_icon == 108 )  icon = 39;  // energy ?
        if ( m_icon == 109 )  icon = 33;  // derrick ?
        if ( m_icon == 110 )  icon = 42;  // nuclear ?
        if ( m_icon == 111 )  icon = 38;  // labo ?
        if ( m_icon == 112 )  icon = 44;  // info ?
        if ( m_icon == 113 )  icon = 46;  // lightning protection ?
        if ( m_icon == 114 )  icon = 47;  // vault ?
        if ( m_icon == 115 )  icon = 48;  // control center?
        uv1.x = (32.0f/256.0f)*(icon%8);
        uv1.y = (32.0f/256.0f)*(icon/8);  // uv texture
        uv2.x = uv1.x+32.0f/256.0f;
        uv2.y = uv1.y+32.0f/256.0f;
        uv1.x += dp;
        uv1.y += dp;
        uv2.x -= dp;
        uv2.y -= dp;
        DrawIcon(pos, dim, uv1, uv2);
    }
}


}

