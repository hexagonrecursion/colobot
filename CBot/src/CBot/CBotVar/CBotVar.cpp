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


#include "CBot/CBotVar/CBotVar.h"

#include "CBot/CBotStack.h"

#include "CBot/CBotInstr/CBotInstr.h"
#include "CBot/CBotVar/CBotVarArray.h"
#include "CBot/CBotVar/CBotVarBoolean.h"
#include "CBot/CBotVar/CBotVarByte.h"
#include "CBot/CBotVar/CBotVarChar.h"
#include "CBot/CBotVar/CBotVarClass.h"
#include "CBot/CBotVar/CBotVarDouble.h"
#include "CBot/CBotVar/CBotVarFloat.h"
#include "CBot/CBotVar/CBotVarInt.h"
#include "CBot/CBotVar/CBotVarLong.h"
#include "CBot/CBotVar/CBotVarPointer.h"
#include "CBot/CBotVar/CBotVarShort.h"
#include "CBot/CBotVar/CBotVarString.h"

#include "CBot/CBotClass.h"
#include "CBot/CBotToken.h"

#include "CBot/CBotEnums.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>


namespace CBot
{

////////////////////////////////////////////////////////////////////////////////
long CBotVar::m_identcpt = 0;

////////////////////////////////////////////////////////////////////////////////
CBotVar::CBotVar( ) : m_token(nullptr)
{
    m_pMyThis = nullptr;
    m_InitExpr = nullptr;
    m_LimExpr = nullptr;
    m_type  = -1;
    m_binit = InitType::UNDEF;
    m_ident = 0;
    m_bStatic = false;
    m_mPrivate = ProtectionLevel::Public;
}

CBotVar::CBotVar(const CBotToken &name) : m_token(new CBotToken(name))
{
    m_pMyThis = nullptr;
    m_InitExpr = nullptr;
    m_LimExpr = nullptr;
    m_type  = -1;
    m_binit = InitType::UNDEF;
    m_ident = 0;
    m_bStatic = false;
    m_mPrivate = ProtectionLevel::Public;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar::~CBotVar( )
{
    delete  m_token;
    delete  m_InitExpr;
    delete  m_LimExpr;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::ConstructorSet()
{
    // nop
}

void CBotVar::Update()
{
}

void CBotVar::SetUserPointer(void* user)
{
}

void CBotVar::KillUserPointer()
{
}

CBotVarUserPointer CBotVar::GetUserPointer()
{
    return {};
}

void CBotVar::SetUniqNum(long n)
{
    m_ident = n;

    if ( n == 0 ) assert(0);
}

////////////////////////////////////////////////////////////////////////////////
long CBotVar::NextUniqNum()
{
    if (++m_identcpt < 10000) m_identcpt = 10000;
    return m_identcpt;
}

////////////////////////////////////////////////////////////////////////////////
long CBotVar::GetUniqNum()
{
    return m_ident;
}

bool CBotVar::Save1State(std::ostream &ostr, CBotContext& context)
{
    // this routine "virtual" must never be called,
    // there must be a routine for each of the subclasses (CBotVarInt, CBotVarFloat, etc)
    // ( see the type in m_type )
    assert(0);
    return false;
}

CBotVar* CBotVar::Create(const std::string& n, CBotType type)
{
    CBotToken name(n);
    return CBotVar::Create(name, CBotTypResult(type));
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::Create(const CBotToken& name, CBotTypResult type)
{
    switch (type.GetType())
    {
    case CBotTypByte:
        return new CBotVarByte(name);
    case CBotTypShort:
        return new CBotVarShort(name);
    case CBotTypChar:
        return new CBotVarChar(name);
    case CBotTypInt:
        return new CBotVarInt(name);
    case CBotTypLong:
        return new CBotVarLong(name);
    case CBotTypFloat:
        return new CBotVarFloat(name);
    case CBotTypDouble:
        return new CBotVarDouble(name);
    case CBotTypBoolean:
        return new CBotVarBoolean(name);
    case CBotTypString:
        return new CBotVarString(name);
    case CBotTypPointer:
        assert(type.GetClass() != nullptr);
    case CBotTypNullPointer:
        return new CBotVarPointer(name, type);
    case CBotTypIntrinsic:
        assert(type.GetClass() != nullptr);
        return new CBotVarClass(name, type);

    case CBotTypClass:
        assert(type.GetClass() != nullptr);
        // creates a new instance of a class
        // and returns the POINTER on this instance
        {
            CBotVarClass* instance = new CBotVarClass(name, type);
            CBotVarPointer* pointer = new CBotVarPointer(name, type);
            pointer->SetPointer( instance->GetPointer() );
            return pointer;
        }

    case CBotTypArrayPointer:
        return new CBotVarArray(name, type);

    case CBotTypArrayBody:
        {
            CBotVarClass* instance = new CBotVarClass(name, type);
            CBotVarArray* array = new CBotVarArray(name, type);
            array->SetPointer( instance->GetPointer() );

            CBotVar*    pv = array;
            while (type.Eq(CBotTypArrayBody))
            {
                type = type.GetTypElem();
                pv = (static_cast<CBotVarArray*>(pv))->GetItem(0, true);            // creates at least the element [0]
            }

            return array;
        }
    }

    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::Create( CBotVar* pVar )
{
    CBotVar*    p = Create(pVar->m_token->GetString(), pVar->GetTypResult(CBotVar::GetTypeMode::CLASS_AS_INTRINSIC));
    return p;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::Create(const std::string& n, CBotTypResult type)
{
    CBotToken    name(n);

    switch (type.GetType())
    {
    case CBotTypByte:
        return new CBotVarByte(name);
    case CBotTypShort:
        return new CBotVarShort(name);
    case CBotTypChar:
        return new CBotVarChar(name);
    case CBotTypInt:
        return new CBotVarInt(name);
    case CBotTypLong:
        return new CBotVarLong(name);
    case CBotTypFloat:
        return new CBotVarFloat(name);
    case CBotTypDouble:
        return new CBotVarDouble(name);
    case CBotTypBoolean:
        return new CBotVarBoolean(name);
    case CBotTypString:
        return new CBotVarString(name);
    case CBotTypPointer:
        assert(type.GetClass() != nullptr);
    case CBotTypNullPointer:
        {
            CBotVarPointer* p = new CBotVarPointer(name, type);
            return p;
        }
    case CBotTypIntrinsic:
        {
            assert(type.GetClass() != nullptr);
            CBotVarClass* p = new CBotVarClass(name, type);
            return p;
        }

    case CBotTypClass:
        // creates a new instance of a class
        // and returns the POINTER on this instance
        {
            assert(type.GetClass() != nullptr);
            CBotVarClass* instance = new CBotVarClass(name, type);
            CBotVarPointer* pointer = new CBotVarPointer(name, type);
            pointer->SetPointer( instance->GetPointer() );
            return pointer;
        }

    case CBotTypArrayPointer:
        return new CBotVarArray(name, type);

    case CBotTypArrayBody:
        {
            CBotVarClass* instance = new CBotVarClass(name, type);
            CBotVarArray* array = new CBotVarArray(name, type);
            array->SetPointer( instance->GetPointer() );

            CBotVar*    pv = array;
            while (type.Eq(CBotTypArrayBody))
            {
                type = type.GetTypElem();
                pv = (static_cast<CBotVarArray*>(pv))->GetItem(0, true);            // creates at least the element [0]
            }

            return array;
        }
    }

    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::Create(const std::string& name, CBotType type, CBotClass* pClass)
{
    CBotVar* pVar = Create(name, CBotTypResult(type, pClass));
    // only CBotTypNullPointer can have pClass == nullptr
    if ( type == CBotTypNullPointer && pClass == nullptr )    // pointer "null" ?
        return pVar;

    if ( type == CBotTypClass || type == CBotTypPointer ||
         type == CBotTypIntrinsic )
    {
        if (pClass == nullptr)
        {
            delete pVar;
            assert(false);
            return nullptr;
        }
        pVar->SetClass( pClass );
    }
    return pVar;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::Create(const std::string& name, CBotClass* pClass)
{
    CBotToken    token( name, "" );
    assert(pClass != nullptr);
    CBotVar*    pVar = Create( token, CBotTypResult( CBotTypClass, pClass ) );
    return        pVar;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Destroy(CBotVar* var)
{
    delete var;
}

////////////////////////////////////////////////////////////////////////////////
CBotTypResult CBotVar::GetTypResult(GetTypeMode mode)
{
    CBotTypResult    r = m_type;

    if ( mode == GetTypeMode::CLASS_AS_POINTER && m_type.Eq(CBotTypClass) )
        r.SetType(CBotTypPointer);
    if ( mode == GetTypeMode::CLASS_AS_INTRINSIC && m_type.Eq(CBotTypClass) )
        r.SetType(CBotTypIntrinsic);

    return r;
}

////////////////////////////////////////////////////////////////////////////////
CBotType CBotVar::GetType(GetTypeMode mode) const
{
    if ( mode == GetTypeMode::CLASS_AS_POINTER && m_type.Eq(CBotTypClass) )
        return CBotTypPointer;
    if ( mode == GetTypeMode::CLASS_AS_INTRINSIC && m_type.Eq(CBotTypClass) )
        return CBotTypIntrinsic;
    return static_cast<CBotType>(m_type.GetType());
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetType(CBotTypResult& type)
{
    m_type = type;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar::InitType CBotVar::GetInit() const
{
    if ( m_type.Eq(CBotTypClass) ) return InitType::DEF;        // always set!

    return m_binit;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetInit(CBotVar::InitType initType)
{
    m_binit = initType;
    if (initType == CBotVar::InitType::IS_POINTER ) m_binit = CBotVar::InitType::DEF;                    // special case

    if ( m_type.Eq(CBotTypPointer) && initType == CBotVar::InitType::IS_POINTER )
    {
        auto instance = GetPointer();
        if ( instance == nullptr )
        {
            instance = (new CBotVarClass(CBotToken(), m_type))->GetPointer();
            SetPointer(instance);
        }
        instance->SetInit(CBotVar::InitType::DEF);
    }

    if ( m_type.Eq(CBotTypClass) || m_type.Eq(CBotTypIntrinsic) )
    {
        CBotVar*    p = (static_cast<CBotVarClass*>(this))->m_pVar;
        while( p != nullptr )
        {
            p->SetInit(initType);
            p->m_pMyThis = static_cast<CBotVarClass*>(this);
            p = p->GetNext();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
const std::string& CBotVar::GetName()
{
    return    m_token->GetString();
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetName(const std::string& name)
{
    m_token->SetString(name);
}

////////////////////////////////////////////////////////////////////////////////
CBotToken* CBotVar::GetToken()
{
    return    m_token;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::GetItem(const std::string& name)
{
    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::GetItemRef(int nIdent)
{
    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::GetItemList()
{
    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::GetItem(int index, bool grow)
{
    assert(0);
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::IsElemOfClass(const std::string& name)
{
    CBotClass*    pc = nullptr;

    if ( m_type.Eq(CBotTypPointer) )
    {
        pc = (static_cast<CBotVarPointer*>(this))->m_pClass;
    }
    if ( m_type.Eq(CBotTypClass) )
    {
        pc = (static_cast<CBotVarClass*>(this))->m_pClass;
    }

    while ( pc != nullptr )
    {
        if ( pc->GetName() == name ) return true;
        pc = pc->GetParent();
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
CBotVar* CBotVar::GetStaticVar()
{
    // makes the pointer to the variable if it is static
    if ( m_bStatic == 0 || m_pMyThis == nullptr ) return this;

    CBotClass*    pClass = m_pMyThis->GetClass();
    return pClass->GetItem( m_token->GetString() );
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetVal(CBotVar* var)
{
    switch (var->GetType())
    {
    case CBotTypBoolean:
        SetValInt(var->GetValInt());
        break;
    case CBotTypByte:
        SetValByte(var->GetValByte());
        break;
    case CBotTypShort:
        SetValShort(var->GetValShort());
        break;
    case CBotTypChar:
        SetValChar(var->GetValChar());
        break;
    case CBotTypInt:
        SetValInt(var->GetValInt(), (static_cast<CBotVarInt*>(var))->m_defnum);
        break;
    case CBotTypLong:
        SetValLong(var->GetValLong());
        break;
    case CBotTypFloat:
        SetValFloat(var->GetValFloat());
        break;
    case CBotTypDouble:
        SetValDouble(var->GetValDouble());
        break;
    case CBotTypString:
        SetValString(var->GetValString());
        break;
    case CBotTypPointer:
    case CBotTypNullPointer:
    case CBotTypArrayPointer:
        SetPointer(var->GetPointer());
        break;
    case CBotTypClass:
        {
            delete (static_cast<CBotVarClass*>(this))->m_pVar;
            (static_cast<CBotVarClass*>(this))->m_pVar = nullptr;
            Copy(var, false);
        }
        break;
    default:
        assert(0);
    }

    m_binit = var->m_binit;        // copy the nan status if it has
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetStatic(bool bStatic)
{
    m_bStatic = bStatic;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetPrivate(ProtectionLevel mPrivate)
{
    m_mPrivate = mPrivate;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::IsStatic()
{
    return m_bStatic;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::IsPrivate(ProtectionLevel level)
{
    return static_cast<int>(m_mPrivate) >= static_cast<int>(level);
}

////////////////////////////////////////////////////////////////////////////////
CBotVar::ProtectionLevel CBotVar::GetPrivate()
{
    return m_mPrivate;
}

void CBotVar::SetPointer(const CBotVarSPtr& pVarClass)
{
    assert(0);
}

CBotVarSPtr CBotVar::GetPointer()
{
    assert(0);
    return nullptr;
}

bool CBotVar::PointerIsUnique() const
{
    assert(0);
    return false;
}

// All these functions must be defined in the subclasses
// derived from class CBotVar

signed char CBotVar::GetValByte() const
{
    assert(0);
    return 0;
}

short CBotVar::GetValShort() const
{
    assert(0);
    return 0;
}

uint32_t CBotVar::GetValChar() const
{
    assert(0);
    return 0;
}

int CBotVar::GetValInt() const
{
    assert(0);
    return 0;
}

long CBotVar::GetValLong() const
{
    assert(0);
    return 0;
}

float CBotVar::GetValFloat() const
{
    assert(0);
    return 0;
}

double CBotVar::GetValDouble() const
{
    assert(0);
    return 0;
}

void CBotVar::SetValByte(signed char val)
{
    assert(false);
}

void CBotVar::SetValShort(short val)
{
    assert(false);
}

void CBotVar::SetValChar(uint32_t val)
{
    assert(false);
}

void CBotVar::SetValInt(int c, const std::string& s)
{
    assert(0);
}

void CBotVar::SetValLong(long val)
{
    assert(false);
}

void CBotVar::SetValFloat(float c)
{
    assert(0);
}

void CBotVar::SetValDouble(double val)
{
    assert(false);
}

void CBotVar::Mul(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Power(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
CBotError CBotVar::Div(CBotVar* left, CBotVar* right)
{
    assert(0);
    return CBotNoErr;
}

////////////////////////////////////////////////////////////////////////////////
CBotError CBotVar::Modulo(CBotVar* left, CBotVar* right)
{
    assert(0);
    return CBotNoErr;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Add(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Sub(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Lo(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Hi(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Ls(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Hs(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Eq(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool CBotVar::Ne(CBotVar* left, CBotVar* right)
{
    assert(0);
    return false;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::And(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Or(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::XOr(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::ASR(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SR(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SL(CBotVar* left, CBotVar* right)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Neg()
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Not()
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Inc()
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Dec()
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::Copy(CBotVar* pSrc, bool bName)
{
    if (bName) *m_token = *pSrc->m_token;
    m_type = pSrc->m_type;
    m_binit = pSrc->m_binit;
//-    m_bStatic    = pSrc->m_bStatic;
    m_next = nullptr;
    m_pMyThis = nullptr;//p->m_pMyThis;

    // keeps indentificator the same (by default)
    if (m_ident == 0) m_ident = pSrc->m_ident;
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetValString(const std::string& val)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
std::string CBotVar::GetValString() const
{
    assert(0);
    return std::string();
}

////////////////////////////////////////////////////////////////////////////////
void CBotVar::SetClass(CBotClass* pClass)
{
    assert(0);
}

////////////////////////////////////////////////////////////////////////////////
CBotClass* CBotVar::GetClass()
{
    assert(0);
    return nullptr;
}

CBotVar::operator bool()
{
    return static_cast<bool>(GetValInt());
}

CBotVar::operator signed char()
{
    return GetValByte();
}

CBotVar::operator short()
{
    return GetValShort();
}

CBotVar::operator uint32_t()
{
    return GetValChar();
}

CBotVar::operator char32_t()
{
    return GetValChar();
}

CBotVar::operator int()
{
    return GetValInt();
}

CBotVar::operator long()
{
    return GetValLong();
}

CBotVar::operator float()
{
    return GetValFloat();
}

CBotVar::operator double()
{
    return GetValDouble();
}

CBotVar::operator std::string()
{
    return GetValString();
}

void CBotVar::operator=(const CBotVar &var)
{
    SetVal(const_cast<CBotVar*>(&var));
}

void CBotVar::operator=(signed char x)
{
    SetValByte(x);
}

void CBotVar::operator=(short x)
{
    SetValShort(x);
}

void CBotVar::operator=(uint32_t x)
{
    SetValChar(x);
}

void CBotVar::operator=(char32_t x)
{
    SetValChar(x);
}

void CBotVar::operator=(int x)
{
    SetValInt(x);
}

void CBotVar::operator=(long x)
{
    SetValLong(x);
}

void CBotVar::operator=(float x)
{
    SetValFloat(x);
}

void CBotVar::operator=(double x)
{
    SetValDouble(x);
}

void CBotVar::operator=(const std::string &x)
{
    SetValString(x);
}

} // namespace CBot
