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
 * \addtogroup MotionBuffer
 * @{
 *
 * \project BlueMarlin
 * \author Kein0r
 *
 * GNU coding standard (https://www.gnu.org/prep/standards/) shall be
 * followed beside the snake_case_thing. Please use camelCase instead.
 *
 *
 */

/* ******************| Inclusions |************************************ */
#include "motionBuffer.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */
RingBuffer<MotionBlock_t, MOTIONBUFFER_MOTIONBUFFER_SIZE> motionBuffer;

/* ******************| Function Implementation |*********************** */

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
