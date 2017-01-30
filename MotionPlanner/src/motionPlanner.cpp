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
 * \brief MotionPlanner source file
 *
 * File names should start with lowercase character and use cammelCase 
 * notation.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 * Reasoning behind the mathematics in this module (in the key of 'Mathematica'):
 *
 * s == speed, a == acceleration, t == time, d == distance
 *
 * Basic definitions:
 *   Speed[s_, a_, t_] := s + (a*t)
 *   Travel[s_, a_, t_] := Integrate[Speed[s, a, t], t]
 *
 * Distance to reach a specific speed with a constant acceleration:
 *   Solve[{Speed[s, a, t] == m, Travel[s, a, t] == d}, d, t]
 *   d -> (m^2 - s^2)/(2 a) --> estimate_acceleration_distance()
 *
 * Speed after a given distance of travel with constant acceleration:
 *   Solve[{Speed[s, a, t] == m, Travel[s, a, t] == d}, m, t]
 *   m -> Sqrt[2 a d + s^2]
 *
 * DestinationSpeed[s_, a_, d_] := Sqrt[2 a d + s^2]
 *
 * When to start braking (di) to reach a specified destination speed (s2) after accelerating
 * from initial speed s1 without ever stopping at a plateau:
 *   Solve[{DestinationSpeed[s1, a, di] == DestinationSpeed[s2, a, d - di]}, di]
 *   di -> (2 a d - s1^2 + s2^2)/(4 a) --> intersection_distance()
 *
 * IntersectionDistance[s1_, s2_, a_, d_] := (2 a d - s1^2 + s2^2)/(4 a)
 *
 */


/** \addtogroup MotionPlanner
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "MotionPlanner.h"
#include <platform.h>
#include <stdlib.h>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */
/**
 * \brief Add a new movement to the motion planner
 * Adds a new movement to the head of the motion planner buffer to be
 * executed. Movements are given as relative (delta) movements in axis
 * coordinates.
 * Because this function shall be used for all kind of configurations macros
 * like X_AXIS shall not be used but instead #MACHINE_NUM_AXIS and
 * #MACHINE_NUM_EXTRUDER used instead.
 * This function is blocking if the buffer can't hold the new motion. If
 * the ringbuffer is full the function will wait until space is available
 * @param[in] deltaMove Incremental move in axis coordinates
 * X_A.
 * @param[in] feedrate Feedrate, that is speed, for this move in steps per
 * second
 * @return TRUE if movement was successfully added to #motionBuffer. FALSE
 * if movement was to small to be added.
 * @note Replaces function plan_buffer_line
 */
bool MotionPlanner::addMovement(AxisCoordinates_t deltaMove, AxisFeedrate_t feedrate)
{
  bool retVal = FALSE;
  MotionBlock_t motion;
  /* If the buffer is full: good! That means we are well ahead of the
   * machine. Rest here until there is room in the buffer.
   */
  while (!motionBuffer.available()) Idle();

  /* TODO: Add PREVENT_DANGEROUS_EXTRUDE and PREVENT_LENGTHY_EXTRUDE here */

  motion.stepEventCount = 0;
  motion.steps.directionBits = STEPPER_DIRECTION_POSITIVE;
  /* Calculate absolute steps for each extruder and set direction bits accordingly */
  for (uint8_t i=0; i<MACHINE_NUM_EXTRUDER; i++)
    {
      /* Transform from axis to stepper coordinates */
      motion.steps[i] = abs(deltaMove.extruder[i]);
      /* Calculate direction bits for this move */
      if (deltaMove.extruder[i] < 0)
        {
          Stepper_setStepDirectionNegative(motion.steps.directionBits, i);
        }
      /* Calculate maximum number of steps needed for this move */
      motion.stepEventCount = max(motion.stepEventCount, motion.steps[i]);
    }

  /* stepEvenCount so far now only contains extruder steps, check and adjust feedrate
   * if this is a travel only move (without extrusion) */
  if (motion.stepEventCount == 0)
    {
      max(feedrate, parameter.minimumTravelFeedrate);
    }
  else
    {
      max(feedrate, parameter.minimumFeedrate);
    }
  /* Calculate absolute steps for each axis stepper and set direction bits accordingly */
  for (uint8_t i=0; i<MACHINE_NUM_AXIS; i++)
    {
      /* Transform from axis to stepper coordinates */
      motion.steps[i] = abs(deltaMove.axis[i]);
      /* Calculate direction bits for this move */
      if (deltaMove.axis[i] < 0)
        {
          Stepper_setStepDirectionNegative(motion.steps.directionBits, i);
        }
      /* Calculate maximum number of steps needed for this move */
      motion.stepEventCount = max(motion.stepEventCount, motion.steps[i]);
    }

  /* Only proceed if block is above threshold */
  if (motion.stepEventCount > MOTIONPLANNER_MINIMUM_SEGMENT_SIZE)
    {
      motion.steps.extruder[extruder]
      for (uint8_t i=0; i<MACHINE_NUM_EXTRUDER; i++)
        {

        }
      /* TODO: Add volumetric_multiplier and extruder_multiplier functionality here
       * motion.steps.e = deltaMove.e * volumetric_multiplier;
       * motion.steps.e = deltaMove.e * extruder_multiplier[EXTRUDER]; */

      /* TODO: Add fan speed control here
       * for (uint8_t i = 0; i < FAN_COUNT; i++) block->fan_speed[i] = fanSpeeds[i];
       */

      /* Enabling stepper was moved to stepper module */

      retVal=TRUE;
    }
  return retVal;
}
/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
