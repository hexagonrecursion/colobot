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

#include <unordered_map>
#include <string>

#include "CBot/CBotInstr/CBotInstr.h"

namespace CBot
{
class CBotCStack;
class CBotToken;

/**
 * \brief Instruction "case", part of "switch" structure
 *
 * \see CBotSwitch
 */
class CBotCase : public CBotInstr
{

public:
    CBotCase();
    ~CBotCase();

    /*!
     * \brief Compile
     * \param p
     * \param pStack
     * \return
     */
    static CBotInstr* Compile(CBotToken* &p, CBotCStack* pStack, std::unordered_map<long, CBotInstr*>& labels);

    /*!
     * \brief Execute Execution of instruction "case".
     * \param pj
     * \return
     */
    bool Execute(CBotStack* &pj) override;

    /*!
     * \brief RestoreState
     * \param pj
     * \param bMain
     */
    void RestoreState(CBotStack* &pj, bool bMain) override;

protected:
    virtual const std::string GetDebugName() override { return "CBotCase"; }
    virtual std::map<std::string, CBotInstr*> GetDebugLinks() override;

private:
    //! List of instructions after case label
    CBotInstr* m_instr;

    friend class CBotSwitch;
};

} // namespace CBot
