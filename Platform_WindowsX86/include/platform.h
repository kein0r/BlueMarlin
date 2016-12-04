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
#if (!defined PLATFORM_INCLUDE_PLATFORM_H_)
/* Preprocessor exclusion definition */
#define PLATFORM_INCLUDE_PLATFORM_H_
/**
 * \file platform.h
 *
 * \brief Platform module include file
 *
 * The inclusion protection does not obey the naming because there shall
 * be only one platform used at a time.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */
/** \addtogroup Platform_WindowsX86
 * @{
 */

/* ******************| Inclusions |************************************ */

/* ******************| Macros |**************************************** */

/* ******************| Type definitions |****************************** */

/* ******************| External function declarations |**************** */
void init(void);
void loop(void);

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( PLATFORM_INCLUDE_PLATFORM_H_ ) */
/* ******************| End of file |*********************************** */
