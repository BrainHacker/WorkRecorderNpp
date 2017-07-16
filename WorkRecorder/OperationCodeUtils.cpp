// 
// OperationCodesUtils.cpp
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

const uint OperationCodesUtils::numMaxIntegerSize = UCHAR_MAX - sizeof(byte) - sizeof(dword); //header + overall size
const uint OperationCodesUtils::numMaxStringSize = OperationCodesUtils::numMaxIntegerSize - sizeof(byte); // + string size

unordered_map<OperationCode, OperationCode> OperationCodesUtils::oppositeOperationCodes =
{
    {OperationCode::insertString, OperationCode::removeString},
    {OperationCode::removeString, OperationCode::insertString},

    {OperationCode::typeString, OperationCode::untypeString},
    {OperationCode::untypeString, OperationCode::typeString},

    {OperationCode::pullString, OperationCode::pushString},
    {OperationCode::pushString, OperationCode::pullString},
};

// static
void OperationCodesUtils::format(ostream& output, OpCodeInfo* opCode)
{
    assert(opCode, Constants::strNullPtr);

    uint totalSize = 0;

    output << (byte)opCode->code;
    totalSize += sizeof(byte);
    
    if (opCode->numField != undefined(opCode->numField))
    {
        uint size = IoUtils::writeVarInteger(output, opCode->numField);
        assert(size <= numMaxIntegerSize, Constants::strOverflow);

        totalSize += size;
    }
    else
    {
        size_t stringSize = opCode->strField.size();
        if (stringSize)
        {
            assert(stringSize <= numMaxStringSize, Constants::strOverflow);
            output << (byte)stringSize;
            totalSize += sizeof(byte);

            output << opCode->strField.c_str();
            totalSize += stringSize;
        }
    }

    totalSize += sizeof(byte);
    assert(totalSize <= UCHAR_MAX, Constants::strOverflow);
    output << (byte)totalSize;

    opCode->clear();
}

// static
OpCodeInfo OperationCodesUtils::parse(istream& input)
{
    OpCodeInfo opCode;

    uint totalSize = 0;
    input >> (byte&)opCode.code;
    totalSize += sizeof(byte);

    switch (opCode.code)
    {
        case OperationCode::pausePlayback:
        //nothing to do
        break;

        case OperationCode::setCursorPosition:
        case OperationCode::sleepTime:
        {
            totalSize += IoUtils::readVarInteger(input, &opCode.numField);
        }
        break;

        case OperationCode::insertString:
        case OperationCode::removeString:
        case OperationCode::typeString:
        case OperationCode::untypeString:
        case OperationCode::pullString:
        case OperationCode::pushString:
        {
            byte size = 0;
            input >> size;
            totalSize += sizeof(byte);

            vector<char> buffer(size);
            input.read(buffer.data(), size);
            opCode.strField = string(buffer.data(), size);
            totalSize += size;
        }
        break;

        default:
            //todo assert
            break;
    }

    byte size = 0;
    input >> size;
    totalSize += sizeof(size);

    assert(totalSize == size, "Format error");
    return opCode;
}

// static
bool OperationCodesUtils::hasOppositeCode(OperationCode code)
{
    return oppositeOperationCodes.find(code) != oppositeOperationCodes.cend();
}

// static
OperationCode OperationCodesUtils::getOppositeCode(OperationCode code)
{
    return oppositeOperationCodes.find(code)->second;
}
