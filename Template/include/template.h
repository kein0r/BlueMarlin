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
#if (!defined TEMPLATE_INCLUDE_TEMPLATE_H_)
/* Preprocessor exclusion definition */
#define TEMPLATE_INCLUDE_TEMPLATE_H_
/**
 * \brief Template include file
 *
 * Include files should start with a lowercase character and use cammelCase
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

/* ******************| Macros |**************************************** */

/**
 * Macros used to define values should always define default values. Numbers
 * shall always have a type
 * It's possible to override default in the respective configuration file
 * or by specifying the value during compile time with
 * -DTEMPLATE_TEMPLATE_THING 4
 */
#ifndef TEMPLATE_TEMPLATE_THING
#define TEMPLATE_TEMPLATE_THING         (uint8_t)5
#endif

/* ******************| Type definitions |****************************** */

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( TEMPLATE_INCLUDE_TEMPLATE_H_ ) */
/* ******************| End of file |*********************************** */
