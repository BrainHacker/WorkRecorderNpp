// 
// IoUtils.cpp
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2017.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/dmitry-zakablukov/WorkRecorderNpp
//
// Work Recorder plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Work Recorder plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Work Recorder plugin. If not, see <http://www.gnu.org/licenses/>.
//

#include "common.h"

// static
uint IoUtils::readVarInteger(istream& input, uhyper* valuePtr)
{
    assert(valuePtr, ::Constants::strNullPtr);
    uhyper& value = *valuePtr;
    value = 0;

    uint totalSize = 0;
    byte currentByte = 0;
    do
    {
        input >> currentByte;
        totalSize += sizeof(byte);
        
        value <<= Constants::numSignificantBitCount;
        value |= currentByte >> (CHAR_BIT - Constants::numSignificantBitCount);
    } while (currentByte & Constants::numContinueBit);

    return totalSize;
}

// static
uint IoUtils::writeVarInteger(ostream& output, uhyper value)
{
    uint totalSize = 0;
    byte currentByte = 0;

    do 
    {
        currentByte = (value & ((1 << Constants::numSignificantBitCount) - 1));
        currentByte <<= (CHAR_BIT - Constants::numSignificantBitCount);

        value >>= Constants::numSignificantBitCount;
        if (value)
            currentByte &= Constants::numContinueBit;

        output << currentByte;
        ++totalSize;
    } while (value);

    return totalSize;
}
