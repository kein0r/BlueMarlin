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
 * /** \addtogroup MotionPlanner
 * @{
 *
 * \brief MotionPlanner source file
 *
 * \project BlueMarlin
 * \author kein0r
 *
 * Motion Planing
 *
 * Motion planning is one of the bigger parts. Motion planing will be done base on
 * * Relative (delta) moves in world coordinates [mm] X_W[mm]
 * * Feed rate, which is speed, in world coordinates F_W[mm/s]
 * The reason for using relative world coordinates is to make the motion planner
 * independent of the actual position of the head.
 * Unfortunately, the motion planner can't be fully  independent of  machine's
 * kinematics. In case of nonlinear machine kinematics motionPlanner needs to split
 * the move into smaller pieces.
 * The name motion planner might be a bit misleading. This module does not only
 * take care of the movement of the head but also about the movement of the
 * filament.
 *
 * The algorithm shall ensure that speed changes, that is jerk [mm/s] or junction
 * speed, between two moves shall not be greater than allowed maximum jerk [mm/s]
 * for the machine.
 * For simplicity (Efficient Jerk Control) it will be assumed that each new move
 * will be in the opposite direction (worst-case) and therefore the overall speed
 * change between to moves shall always be below maximum allowed jerk. This
 * implementation is more efficient regarding CPU time, however, less efficient
 * regarding printing time.
 * Future implementation (Advanced Jerk Control) can consider change of speed
 * vector to calculate the real jerk between two moves reducing slow-down between
 * to moves to a minimum.
 * Acceleration from junction speed to requested speed, that is feedrate, shall
 * not be higher than maximum allowed acceleration for the machine. If feedrate
 * can't be reached for this move, a lower speed shall be used instead that ensures
 * acceleration and de-acceleration from and to junction speed which obeys machine
 * maximum values for acceleration and jerk.
 *
 * Efficient Jerk Control
 *
 * Last mode: speed of last move s-1, speed of actual move s
 * s-1 > max_jerk/2, s > max_jerk/2 -> junction speed: max_jerk/2
 * s-1 > max_jerk/2, s < max_jerk/2 -> junction speed: max_jerk-s
 * s-1 < max_jerk/2, s < max_jerk/2 -> junction speed: min(s-1, s)
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

/* ******************| Inclusions |************************************ */
#include "MotionPlanner.h"
#include <platform.h>
#include <motionBuffer.h>
#include <stdlib.h>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */
/**
 * \brief Add a new movement to the motion planner
 * Adds a new movement to the head of the motion planner buffer to be
 * executed. Movements are given in world coordinates. World koordinates
 * as well as feedrate are assumed to be corrected or adapted
 * already. This means, among other things,
 * * Feedrate was adapted by feedrate multiplier, minimumTravelFeedrate, minimumFeedrate (for E only moves)
 * * Feedrate was limited to maximum feedrate
 * * Coordinates are corrected by bed leveling etc. matrix
 *
 * For nonlinear kinematics the move will be split into segments. It is
 * assumed that even nonlinear kinematics are smooth functions and therefore
 * no jerk control is applied on the segments.
 *
 * Because this function shall be used for all kind of machines configurations
 * macros like X_AXIS shall not be used but instead #MACHINE_NUM_AXIS and
 * #MACHINE_NUM_EXTRUDER used instead.
 * This function is blocking if the buffer can't hold the new motion. If
 * the ringbuffer is full the function will will call Idle() until buffer is
 * free again.
 *
 * This function is split into the following parts.
 * 1. Calculate base values for this move: Length of move in world coordinates [mm]
 * number of segments and time for each segment [s]
 * 2. For all segments of this move: Calculate the necessary steps using inverse machine
 * kinematics
 * 3. Calculate and limit acceleration for this move
 * 4. Calculate and limit jerk, that is speed changes between to consecutive blocks, for this move
 * @param[in] targetPositionW Absolute target position of head in world coordinates
 * X_W [mm] and relative extruder coordinates E_W [mm].
 * @param[in] feedrateW Feedrate, that is speed, for this move in mm/s (f_W [mm/s])
 * @return TRUE
 * @note Replaces function plan_buffer_line and prepare_move_delta
 */
bool MotionPlanner::addLineMovement(WorldCoordinates_t targetPositionW, WorldCoordinate_t feedrateW)
{
  bool retVal = RESULT_NOT_OK;
  WorldCoordinates_t segmentMoveW;
  AxisCoordinates_t stepsA, segmentStepsA;
  MotionBlock_t motion;

  /* Step 1: Calculate base values for this move: Length of move in world coordinates [mm] number
   * of segments and time for each segment [s] */
  /* First calculate the length for the complete move */
  segmentMoveW.x = (targetPositionW.x - worldPosition.x);
  segmentMoveW.y = (targetPositionW.y - worldPosition.y);
  segmentMoveW.z = (targetPositionW.z - worldPosition.z);
  segmentMoveW.e = (targetPositionW.e - worldPosition.e);
  /* Calculate length, travel time and speed for for this move.
   * Because this is a line movement in world coordinates, those values are constant during the move
   * and therefore calculated only once */
  WorldCoordinate_t totalTravelLengthW = sqrt(sq(segmentMoveW.x) + sq(segmentMoveW.y) + sq(segmentMoveW.z));
  float totalTravelTime = totalTravelLengthW / feedrateW;
  float travelSpeedW = totalTravelLengthW / totalTravelTime;

  int segments = max(1, parameter.segmentsPerSecond * totalTravelTime);
  float segmentTravelTime = totalTravelTime / segments;

  /* All segments are of equal length. Therefore we calculate it once now that we know how many
   * segments we are going to do. */
  segmentMoveW.x = segmentMoveW.x / segments;
  segmentMoveW.y = segmentMoveW.y / segments;
  segmentMoveW.z = segmentMoveW.z / segments;
  segmentMoveW.e = segmentMoveW.e / segments;

  /* Iterate over all segments of this move. Iterator starts from one for easier
   * calculation later on.
   */
  for (int segment=1; segment <= segments; segment++)
    {
      /* Step 2. For all segments of this move: Calculate the necessary steps using inverse
       *  machine kinematics */
      /* We directly increment the position pretending that the move was already done */
      worldPosition.x += segmentMoveW.x;
      worldPosition.y += segmentMoveW.y;
      worldPosition.z += segmentMoveW.z;
      worldPosition.e += segmentMoveW.e;

      /* Transform from world into axis coordinate systems */
      kinematic.inverseMachineKinematic(worldPosition, &segmentStepsA, activeExtruder);

      motion.stepEventCount = 0;
      motion.steps.directionBits = STEPPER_DIRECTION_POSITIVE;

      /* Calculate the delta steps. Extruder coordinates are always relative. Therefore
       * no delta needs to be calculated */
      for (uint8_t i=0; i<MACHINE_NUM_AXIS; i++)
        {
	  segmentStepsA.axis[i] = segmentStepsA.axis[i] - axisPosition.axis[i];
	  /* Transform from axis to stepper coordinates */
	  motion.steps[i] = abs(segmentStepsA.axis[i]);
	  /* Calculate direction bits for this move */
	  if (segmentStepsA.axis[i] < 0)
	    {
	      Stepper_setStepDirectionNegative(motion.steps.directionBits, i);
	    }
	  /* Calculate maximum number of steps needed for this move */
	  motion.stepEventCount = max(motion.stepEventCount, motion.steps[i]);
        }
      for (uint8_t i=0; i<MACHINE_NUM_EXTRUDER; i++)
	{
	  /* Transform from axis to stepper coordinates */
	  motion.steps[i] = abs(segmentStepsA.extruder[i]);
	  /* Calculate direction bits for this move */
	  if (segmentStepsA.extruder[i] < 0)
	    {
	      Stepper_setStepDirectionNegative(motion.steps.directionBits, i);
	    }
	  /* Calculate maximum number of steps needed for this move */
	  motion.stepEventCount = max(motion.stepEventCount, motion.steps[i]);
	}
      /* Only proceed if block steps are above threshold */
      if (motion.stepEventCount > MOTIONPLANNER_MINIMUM_SEGMENT_SIZE)
        {

	  motion.nominalRate = segmentTravelTime / motion.stepEventCount;

	  /* @todo: Rpelace with correct code. For movment smothing (i.e. jerk control)
	   * is ont applied.*/
	  motion.
	  /* If the buffer is full: good! That means we are well ahead of the
	   * machine. Rest here until there is room in the buffer.
	  */
	  while (!motionBuffer.available()) Idle();

	  motionBuffer.write(motion);
	  retVal = RESULT_OK;
        }
    }
  return retVal;
}





    /* Only proceed if block steps are above threshold */
    if (motion.stepEventCount > MOTIONPLANNER_MINIMUM_SEGMENT_SIZE)
      {
	/* TODO: Add volumetric_multiplier and extruder_multiplier functionality here
	 * motion.steps.e = deltaMoveW.e * volumetric_multiplier;
	 * motion.steps.e = deltaMove.e * extruder_multiplier[EXTRUDER]; */

	/* TODO: Add fan speed control here
	 * for (uint8_t i = 0; i < FAN_COUNT; i++) block->fan_speed[i] = fanSpeeds[i];
	 */

	/* Enabling stepper was moved to stepper module */
	/* ******** 2. Calculate and limit speed for this move ******** */

	/* Calculate overall length [steps] of this move */
	AxisCoordinate_t travelLength = 0;
	for (uint8_t i=0; i<MACHINE_NUM_AXIS; i++)
	  {
	    travelLength += deltaMove.axis[i] * deltaMove.axis[i];
	  }
	travelLength = sqrt(travelLength);
	/* Calculate the speed for each axis [steps/sec] */
	AxisCoordinates_t travelSpeed;
	for (uint8_t i=0; i<MACHINE_NUM_AXIS; i++)
	  {
	    travelSpeed.axis[i] = feedrate * deltaMove.axis[i] / travelLength;
	  }
	/* Finally, to be executed, add the block to motion buffer. Because we waited for
	 * space earlier, the motion will always be added */

	previousTravelSpeed = travelSpeed;

      }
    } // for (int i=0; i< segments; i++)
  /* Save speed for next run */
}
/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
