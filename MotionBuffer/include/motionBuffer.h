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
#if (!defined MOTIONBUFFER_INCLUDE_MOTIONBUFFER_H_)
/* Preprocessor exclusion definition */
#define MOTIONBUFFER_INCLUDE_MOTIONBUFFER_H_
/**
 * \addtogroup MotionBuffer
 * @{
 *
 * Simple, almost empty module just to define and implement the motion
 * buffer.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/* ******************| Inclusions |************************************ */

/* ******************| Macros |**************************************** */
/**
 * Default number of entries in #Motionplanner ringbuffer #motionbuffer.
 * Its possible to override default in the respective configuration file
 * or by specifying the value during compile time with
 * -DMOTIONBUFFER_MOTIONBUFFER_SIZE 32
 */
#ifndef MOTIONBUFFER_MOTIONBUFFER_SIZE
#define MOTIONBUFFER_MOTIONBUFFER_SIZE        (uint8_t)32
#endif


/* ******************| Type definitions |****************************** */

/**
 * All information needed for one move.
 * @note activeExtruder was moved to machine/kinematic module. This way
 * retract one extruder while at the same time extrude with another one
 * is possible.
 */
typedef struct
{
  StepperCoordinates_t steps;           /*!< Number of absolute steps for this move along each axis */
  StepperCoordinate_t stepEventCount;   /*!< Maximum number of step events required to complete this block */

  StepperCoordinate_t nominalSpeed;     /*!< Nominal speed for this block, that is #stepEvenCount/time, in steps/sec */
  StepperCoordinate_t maxEntrySpeed;    /*!< Maximum allowable junction entry speed based on speed in steps/sec */
  StepperCoordinate_t entrySpeed;       /*!< Entry speed at previous-current block junction in steps/sec */
} MotionBlock_t;

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */
extern RingBuffer<MotionBlock_t, MOTIONBUFFER_MOTIONBUFFER_SIZE> motionBuffer;

/** @} doxygen end group definition */
#endif /* if !defined( MOTIONBUFFER_INCLUDE_MOTIONBUFFER_H_ ) */
/* ******************| End of file |*********************************** */
