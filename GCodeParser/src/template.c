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
 * \file template.c
 *
 * \brief Template source file
 *
 * File names should start with lowercase character and use cammelCase 
 * notation.
 *
 * \project BlueMarlin
 * \author <FULL NAME>
 *
 */


/** \addtogroup Template
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "template.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */
int Template_templateFunction(int i, int *s);


/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */
/**
 * \brief Template function
 * Document your function here. Function names shall start with module names
 * followed by an underscore followed by the function name starting with a 
 * lowercase letter using cammelCase notion.
 * Dont' forget to also describe the parameters of your function including
 * their direction. Also describe the return values, if any.
 * @param[in]  		i	Example input parameter
 * @param[in/out]	i	Example input/output parameter
 * @return			This function returns result X
*/
int Template_templateFunction(int i, int *s)
{
	return i;
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
