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

std::unordered_map<OperationCode, OperationCode> OperationCodesUtils::oppositeOperationCodes =
{
    {OperationCode::insertString, OperationCode::removeString},
    {OperationCode::removeString, OperationCode::insertString},

    {OperationCode::typeString, OperationCode::untypeString},
    {OperationCode::untypeString, OperationCode::typeString},

    {OperationCode::pullString, OperationCode::pushString},
    {OperationCode::pushString, OperationCode::pullString},
};

// static
void OperationCodesUtils::format(std::ostream& output, const OpCodeInfo& opCode)
{
    output << (byte)opCode.code;
    
    bool hasContent = true;
    if (opCode.numField != undefined(opCode.numField))
    {
        // todo: write variable int
        output << opCode.numField;
    }
    else if (opCode.strField.size())
    {
        // todo: write variable int for size
        output << opCode.strField.size();
        output << opCode.strField.c_str();
        output << opCode.strField.size();
    }
    else
    {
        hasContent = false;
    }

    if (hasContent)
    {
        if (hasOppositeCode(opCode.code))
            output << (byte)getOppositeCode(opCode.code);
        else
            output << (byte)opCode.code;
    }
}

// static
OpCodeInfo OperationCodesUtils::parse(std::istream& input)
{
    OpCodeInfo opCode;
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
