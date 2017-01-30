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
#if (!defined PARAMETER_INCLUDE_PARAMETER_H_)
/* Preprocessor exclusion definition */
#define PARAMETER_INCLUDE_PARAMETER_H_
/**
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup Parameter
 * @{
 */

/* ******************| Inclusions |************************************ */

/* ******************| Macros |**************************************** */

/* ******************| Type definitions |****************************** */
/**
 * Struct to store all machine parameter. To be interrupt save changing the
 * parameters is only allowed. Reading can be done by directly accessing the
 * struct elements.
 * Each parameter shall be set during initialization of the module which
 * defines the default value for the respective parameter.
 * All parameter are grouped in a struct for easier storage in EEPROM.
 */
typedef struct {
    uint8_t version;
    AxisCoordinates_t axisStepsPerUnit;                                /*!< Millimeter to steps factor for each axis */
    AxisCoordinates_t volumetric_multiplier[MACHINE_NUM_EXTRUDER];     /*!< Extrude factor (in percent) for each extruder individually */
    AxisCoordinates_t minimumFeedrate;                                 /*!< Minumum Feedrate for moves in steps/sec */
    AxisCoordinates_t minimumTravelFeedrate;                           /*!< Minumum Feedrate for travel moves in steps/sec */
} Parameter_t;

extern Parameter_t parameter;

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( PARAMETER_INCLUDE_PARAMETER_H_ ) */
/* ******************| End of file |*********************************** */
