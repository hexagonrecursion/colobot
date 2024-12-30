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

#include "CBot/context/external_call_list_interface.h"
#include "CBot/context/list_constant_interface.h"

#include "CBot/stdlib/stdlib_public.h"

#include <memory>
#include <unordered_map>

namespace CBot
{
class CBotContext;
class CBotVar;

using CBotContextSPtr = std::shared_ptr<CBot::CBotContext>;
using CBotFileAccessHandlerUPtr = std::unique_ptr<CBot::CBotFileAccessHandler>;

class CBotContext :
    public std::enable_shared_from_this<CBotContext>,
    public CBotExternalCallListInterface,
    public CBotListConstantInterface
{
private:
    CBotContext();

    CBotContext(const CBotContextSPtr& outer);

public:
    [[nodiscard]] static CBotContextSPtr CreateGlobalContext();

    [[nodiscard]] static CBotContextSPtr Create(const CBotContextSPtr& outer);

    /**
     * \brief Destructor
     */
    virtual ~CBotContext();

    /**
     * \brief Generate unique identifier for functions, etc.
     */
    long GetNewUniqueID()
    {
        return m_globalData->m_nextUniqueID++;
    }

    long FindInstance(CBotVar* var) const;
    CBotVar* FindInstance(long pos) const;
    void ClearInstanceList();
    void DeclareInstance(long pos, CBotVar* var);

    bool IsDefinedConstant(const std::string& name) const override;

    const CBotVarUPtr& GetDefinedConstant(const std::string& name) override;

    CBotFileAccessHandler* GetFileAccessHandler() const;

    void SetFileAccessHandler(CBotFileAccessHandlerUPtr fileHandler);

private:
    CBotContextSPtr m_outerContext;

    struct GlobalData
    {
        long m_nextUniqueID = 10000;
        CBotFileAccessHandlerUPtr m_fileHandler;
        std::unordered_map<long, CBotVar*> m_instances;
    };
    std::shared_ptr<CBotContext::GlobalData> m_globalData;
};

} // namespace CBot
