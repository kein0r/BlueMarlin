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
 * \brief GCodeReader 
 *
 * Read g-codes from different sources, compresses them and add them to
 * #GCodeRingBuffer.
 *
 * @note: Replaces the following functions
 * - get_serial_commands: Reads command from serial, analyze it and adds to buffer
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup GCodeReader
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "gCodeReader.h"
#include <gCodeRingBuffer.h>
#include <ctype.h>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */
void GCodeReader_readGCodeSerial();
void GCodeReader_addGCode(uint8_t *data);


/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

/**
 * \brief Reads one g-code from serial line
 *
 * Reads g-codes from different sources, currently serial and sd-card. 
 * One line at a time is read. The buffer for reading g-codes is provided
 * by this module.
 * After g-codes are read they are parsed and written to cyclic buffer.
 * How many g-code lines are read during one call is controlled by 
 * #GCODEREADER_NUMBEROFGCODESTOREAD
*/
void GCodeReader_readGCodeSerial()
{
  char gCodeBuffer[GCODEREADER_GCODEBUFFER_SIZE];
  uint8_t numberOfBytesRead = 0;
  
  for (int i=0; i<GCODEREADER_NUMBEROFGCODESTOREAD; i++)
  {
    numberOfBytesRead = Serial.Read(*gCodeBuffer, GCODEREADER_GCODEBUFFER_SIZE)
    if (numberOfBytesRead > 0)
    {
      GCodeReader_addGCode(&gCodeBuffer);
    }
  }
}

/** 
 * \brief Analyses, compresses and inserts g-code data in #data into ringbuffer
 *
 * Compresses the g-code data in #data 
 * - Removes the following special fields (see http://reprap.org/wiki/Gcode#Special_fields)
 * -- N: Line number
 * -- Checks and removes "*: Checksum"
 * - Removes any blanc character, that is, blanc or tab
 * @param[in/out] data Pointer to buffer holding g-code data. A null terminated string
 * is expected.
 */
void GCodeReader_addGCode(uint8_t *data)
{
  bool ignoreUntilNextValidChar = false;
  uint8_t *nextChar = data; /* Place to write next character for in-place compression */
  uint8_t calculatedCRC = 0x00;
  
  /* Parse the complete string first to calculate CRC and do in-place compression */
  while (data++)
  {
    /* Calculate CRC according to formula found at http://reprap.org/wiki/Gcode#Checking */
    calculatedCRC ^= *data;
    /* Convert the character to upper case */
    *data = toupper(*data);
    switch (*data)
    {
    case 'N':
    case '*':
    case ' ':
    case '\t':
      ignoreUntilNextValidChar = true;
      break;
    case 'G':
    case 'M':
    case 'T':
    case 'S':
    case 'P':
    case 'X':
    case 'Y':
    case 'Z':
    case 'I':
    case 'J':
    case 'D':
    case 'H':
    case 'F':
    case 'R':
    case 'E':
      ignoreUntilNextValidChar = false;
    break;
    default:
      break;
    }
    /* Only add character to buffer if valid */
    if (ignoreUntilNextValidChar == false)
    {
      /* Write data in same buffer but at different location if compressed */
      *nextChar = *data;
      nextChar++;
    }
    else
    {
      /* do nothing */
    }
  } /* while (data++) */
  /* Write null termination at the end of compressed string */
  *nextChar = '\0';
  
  /** @todo Add CRC check here */
  
  /* Now write the compressed string to ringbuffer */
  
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
