// 
// OperationCode.h
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

#pragma once

/// Enumeration of supported operations codes and their brief description
enum OperationCode
{
    // common operations

    /// <summary>
    /// Set cursor to specified position.
    /// <para>Format: operation code (1 byte), cursor position (4 bytes), operation code (1 byte).</para>
    /// </summary>
    setCursorPosition = 0,

    /// <summary>
    /// Insert whole string.
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for removing the string(1 byte).</para>
    /// </summary>
    insertString,

    /// <summary>
    /// Remove whole string (opposite to insertString).
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for inserting the string(1 byte).</para>
    /// </summary>
    removeString,

    /// <summary>
    /// Normal typing.
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for untyping the string(1 byte).</para>
    /// </summary>
    typeString,
    /// <summary>
    /// Erasing string using Backspace key (opposite to typeString).
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for typing the string(1 byte).</para>
    /// </summary>
    untypeString,

    /// <summary>
    /// Erasing string using Delete key.
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for pushing the string(1 byte).</para>
    /// </summary>
    pullString,
    /// <summary>
    /// Type string without changing cursor position (opposite to pullString).
    /// <para>Format: operation code (1 byte), string length (4 bytes), raw string data (char[]),
    /// string length (4 bytes), operation code for pulling the string(1 byte).</para>
    /// </summary>
    pushString,

    // additional operations

    /// <summary>
    /// Sleep specified amount of time in ms before proceeding.
    /// <para>Format: operation code (1 byte), sleep time in ms (4 bytes), operation code (1 byte).</para>
    /// </summary>
    sleepTime,

    /// <summary>
    /// Pause playback until user continue it.
    /// <para>Format: operation code (1 byte).</para>
    /// </summary>
    pausePlayback,

    /// <summary>
    /// Total amount of supported operations.
    /// </summary>
    totalCount,

    /// <summary>
    /// Flag to be inserted between operations (for synchronization purpose).
    /// </summary>
    delimiterFlag = 0xFF,
};

struct OpCodeInfo
{
    OperationCode code;
    std::string strField;
    qword numField = undefined(numField);
};