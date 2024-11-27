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

#include <gtest/gtest.h>
#include <clocale>
#include <memory>
#include <string>

#include "common/logger.h"

extern bool g_cbotTestSaveState;

int main(int argc, char* argv[])
{
    CLogger logger;

    ::testing::InitGoogleTest(&argc, argv);

    setlocale(LC_ALL, "en_US.UTF-8");

    // parse arguments not removed by InitGoogleTest
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if (arg == "--CBotUT_TestSaveState")
            g_cbotTestSaveState = true;
    }

    return RUN_ALL_TESTS();
}
