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
  /**
   * Position of the machine in world coordinates after all moves in the
   * buffer are finished. Thus, as long as the machine is moving this is
   * not the actual position but rather the position that is requested.
   * @TODO Decide if to move to kinematics or machine module
   */
  WorldCoordinates_t worldPosition;

  /**
   * Position for each stepper motor in axis coordinates after all moves
   * in the buffer are finished. Thus, as long as the machine is moving
   * this is not the actual position but rather the position that is
   * requested.
   * @TODO Decide if to move to kinematics or machine module
   */
  AxisCoordinates_t axisPosition;

  /**
   * Currently active extruder
   * @TODO Decide if to move to machine module
   */
  uint8_t activeExtruder = 0;

public:
  bool addLineMovement(WorldCoordinates_t deltaMove, WorldCoordinate_t feedrate);

};

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( MOTIONPLANNER_INCLUDE_MOTIONPLANNER_H_ ) */
/* ******************| End of file |*********************************** */
