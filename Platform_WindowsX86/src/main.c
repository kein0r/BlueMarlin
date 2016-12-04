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
 * \file main.c
 *
 * \brief Template source file
 *
 * File names should start with lowercase character and use cammelCase 
 * notation.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup Platform_WindowsX86
 * @{
 */

/* ******************| Inclusions |************************************ */
#include <time.h>
#include "platform.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

/*
 * \brief main function to be implemented by each platform
 *
 * The main purpose of the main function will be to trigger the loop init and loop 
 * functions known from Aruduino framework.
 * As this is the main function it obviously does not use the existing naming
 * conventions.
 *
 * @return return value to Os
 */
int main()
{
  /* Call init function normally used by Aurduino framework */
  setup();

  /* enter forever loop */
  while (1)
  {
    loop();
  }
  return 0;
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
