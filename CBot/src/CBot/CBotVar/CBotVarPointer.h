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

#include "CBot/CBotVar/CBotVar.h"

namespace CBot
{

/**
 * \brief CBotVar subclass for managing pointers to classes (::CBotTypPointer)
 */
class CBotVarPointer : public CBotVar
{
public:
    /**
     * \brief Constructor. Do not call directly, use CBotVar::Create()
     */
    CBotVarPointer(const CBotToken& name, CBotTypResult& type);
    /**
     * \brief Destructor. Do not call directly, use CBotVar::Destroy()
     */
    ~CBotVarPointer();

    void Copy(CBotVar* pSrc, bool bName = true) override;

    void SetClass(CBotClass* pClass) override;
    CBotClass* GetClass() override;

    CBotVar* GetItem(const std::string& name) override;
    CBotVar* GetItemRef(int nIdent) override;
    CBotVar* GetItemList() override;
    std::string GetValString() const override;

    void SetPointer(const CBotVarSPtr& p) override;
    CBotVarSPtr GetPointer() override;
    bool PointerIsUnique() const override;

    void ConstructorSet() override;

    bool Save1State(std::ostream &ostr, CBotContext& context) override;

    void Update() override;
    void SetUserPointer(void* user) override;
    void KillUserPointer() override;
    VarUserPointer GetUserPointer() override;

    bool Eq(CBotVar* left, CBotVar* right) override;
    bool Ne(CBotVar* left, CBotVar* right) override;

private:
    //! Class pointed to
    CBotVarSPtr m_pVarClass;
    //! Class type
    CBotClass* m_pClass;
    friend class CBotVar;
};

} // namespace CBot
