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
/**
 * \brief Return values to be used by all functions
 */
#define RESULT_OK       (uint8_t)1
#define RESULT_NOT_OK   (uint8_t)0

/* ******************| Type definitions |****************************** */

/**
 * Platform module shall specify the following data types. 
 * - uint8_t, int8_t,
 * - uint16_t, int16_t,
 * - uint32_t, int32_t
 * Normally they are specified in stdint.h, however, this will invoke one
 * more external reference and is therefore avoided. The following is a 
 * copy of mingw's stdint.h file.
 */
typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned   uint32_t;

/*
 * Platform module shall specify bool datatype and TRUE/FALSE.
 * @note Not sure how this works in conjunction with the cpp bool definition.
 */
 #ifndef __cplusplus
typedef unsigned char bool;
#endif
#undef FALSE
#undef TRUE
#define FALSE	0
#define TRUE	1

/* ******************| External function declarations |**************** */
extern void setup(void);
extern void loop(void);

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( PLATFORM_INCLUDE_PLATFORM_H_ ) */
/* ******************| End of file |*********************************** */
