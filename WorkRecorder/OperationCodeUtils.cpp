// 
// OperationCodesUtils.cpp
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2014.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/BrainHacker/WorkRecorderNpp
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
void OperationCodesUtils::format(std::ostream& output, const OpCode& opCode)
{
    output << (byte)opCode.code;
    
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

    output << (byte)opCode.code;
}

// static
OpCode OperationCodesUtils::parse(std::istream& input)
{
    OpCode opCode;
    return opCode;
}
