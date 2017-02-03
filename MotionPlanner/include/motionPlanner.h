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
#if (!defined MOTIONPLANNER_INCLUDE_MOTIONPLANNER_H_)
/* Preprocessor exclusion definition */
#define MOTIONPLANNER_INCLUDE_MOTIONPLANNER_H_
/**
 * \brief MotionPlanner include file
 *
 * Include files should start with a lowercase character and use cammelCase
 * notation.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup MotionPlanner
 * @{
 */

/* ******************| Inclusions |************************************ */
#include<BlueMarlin.h>
#include<RingBuffer.h>

/* ******************| Macros |**************************************** */

/**
 * Minimum number of steps for one movement. Everything with less than
 * this number of steps will be ignored as move and must be joined with
 * the next movement by the next upper layer.
 * It's possible to override default in the respective configuration file
 * or by specifying the value during compile time with
 * -DMOTIONPLANNER_MINIMUM_SEGMENT_SIZE 5
 */
#ifndef MOTIONPLANNER_MINIMUM_SEGMENT_SIZE
#define MOTIONPLANNER_MINIMUM_SEGMENT_SIZE     (StepperCoordinate_t)5
#endif

/* ******************| Type definitions |****************************** */

class MotionPlanner
{
private:
  WorldCoordinates_t previousSpeed;

public:
  bool addLineMovement(AxisCoordinates_t deltaMove, WorldCoordinates_t speed, AxisFeedrate_t feedrate);

};

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( MOTIONPLANNER_INCLUDE_MOTIONPLANNER_H_ ) */
/* ******************| End of file |*********************************** */
