/**
 * BlueMarlin 3D Printer Firmware
 * Copyright (C) 2016 BlueMarlinFirmware [https://github.com/kein0r/BlueMarlin]
 *
 * Based on Marlin, Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#if (!defined GCODEREADER_INCLUDE_GCODEPARSER_H_)
/* Preprocessor exclusion definition */
#define GCODEREADER_INCLUDE_GCODEPARSER_H_
/**
 * \file gCodeParser.h
 *
 * \brief GCodeReader include file
 *
 * Include files should start with a lowercase character and use cammelCase
 * notation.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup GCodeReader
 * @{
 */

/* ******************| Inclusions |************************************ */
#include <platform.h>

/* ******************| Macros |**************************************** */
/**
 * Buffer to read g-codes from different source, currently serial and
 * sd-card.
 */
#ifndef GCODEREADER_GCODEBUFFER_SIZE
#define GCODEREADER_GCODEBUFFER_SIZE      (uint8_t)20
#endif

/**
 * Number of lines to read from each of the sources during on call of 
 * #GCodeReader_readGCodeSerial. This number must be chosen big enough to 
 * not lose g-codes in serial buffer but should also chose small enough
 * to not block the system for too long
 */
#ifndef GCODEREADER_NUMBEROFGCODESTOREAD
#define GCODEREADER_NUMBEROFGCODESTOREAD  (uint8_t)4
#endif

/* ******************| Type definitions |****************************** */

/* ******************| External function declarations |**************** */
extern void GCodeReader_readGCodeSerial();
extern void GCodeReader_addGCode(uint8_t *data);

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( GCODEREADER_INCLUDE_GCODEPARSER_H_ ) */
/* ******************| End of file |*********************************** */
