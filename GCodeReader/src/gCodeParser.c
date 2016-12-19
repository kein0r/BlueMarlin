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
/**
 * \file gCodeParser.c
 *
 * \brief GCodeParser 
 *
 * Parses a single g-code (string) line and adds it to GCodeRingBuffer if 
 * valid g-code was found.
 *
 * @note: Replaces the following functions
 * - get_serial_commands: Reads command from serial, analyze it and adds to buffer
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup GCodeParser
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "gCodeParser.h"
#include <gCodeRingBuffer.h>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */
int GCodeParser_templateFunction(int i, int *s);


/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

void readGCodes()
{
  parse(readGcodesFromSerial());
  
}
/**
 * Parses a single g-code (string) line and adds it to GCodeRingBuffer if 
 * valid g-code was found. The g-code will be ignored if
 * - 

 * @param[in]  		i	Example input parameter
 * @param[in/out]	i	Example input/output parameter
 * @return			This function returns result X
*/
int GCodeParser_parse(char *data)
{
	while (*
	return i;
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
