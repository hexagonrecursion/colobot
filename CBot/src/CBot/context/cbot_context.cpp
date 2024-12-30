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

#include "CBot/context/cbot_context.h"

#include "CBot/stdlib/stdlib_public.h"

namespace CBot
{

CBotContextSPtr CBotContext::CreateGlobalContext()
{
    auto newContext = std::shared_ptr<CBotContext>(new CBotContext);
    InitErrorConstants(newContext);
    InitMathLibrary(newContext);

    return newContext;
}

CBotContextSPtr CBotContext::Create(const CBotContextSPtr& outer)
{
    auto newContext = std::shared_ptr<CBotContext>(new CBotContext(outer));
    InitErrorConstants(newContext);
    InitMathLibrary(newContext);

    return newContext;
}

CBotContext::CBotContext() :
    std::enable_shared_from_this<CBotContext>(),
    m_outerContext(nullptr),
    m_globalData(std::make_shared<CBotContext::GlobalData>())
{
}

CBotContext::CBotContext(const CBotContextSPtr& outer) :
    std::enable_shared_from_this<CBotContext>(),
    m_outerContext(outer),
    m_globalData(outer->m_globalData)
{
}

CBotContext::~CBotContext()
{
}

void CBotContext::ClearInstanceList()
{
    m_globalData->m_instances.clear();
}

void CBotContext::DeclareInstance(long pos, CBotVar* var)
{
    m_globalData->m_instances[pos] = var;
}

CBotVar* CBotContext::FindInstance(long pos) const
{
    auto it = m_globalData->m_instances.find(pos);
    if (it != m_globalData->m_instances.end()) return it->second;
    return nullptr;
}

long CBotContext::FindInstance(CBotVar* var) const
{
    for (const auto& item : m_globalData->m_instances)
        if (item.second == var) return item.first;
    return -1;
}

bool CBotContext::IsDefinedConstant(const std::string& name) const
{
    if (!m_listConstant.IsDefinedConstant(name))
        return m_outerContext && m_outerContext->IsDefinedConstant(name);
    return true;
}

const CBotVarUPtr& CBotContext::GetDefinedConstant(const std::string& name)
{
    if (!m_outerContext || m_listConstant.IsDefinedConstant(name))
        return m_listConstant.GetDefinedConstant(name);
    return m_outerContext->GetDefinedConstant(name);
}

} // namespace CBot
