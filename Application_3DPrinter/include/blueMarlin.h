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
 * \author kein0r
 *
 */


/** \addtogroup Template
 * @{
 */

/* ******************| Inclusions |************************************ */
#include<platform.h>

/* ******************| Macros |**************************************** */
/**
 * Function like macros to set direction bits of stepper motors
 * @TODO Move to stepper module
 */
#define STEPPER_DIRECTION_POSITIVE    (uint8_t)0
#define STEPPER_DIRECTION_NEGATIVE    (uint8_t)1
#define Stepper_setStepDirectionPositive(directionBitVector, stepper)  (directionBitVector |= _BV(stepper))
#define Stepper_setStepDirectionNegative(directionBitVector, stepper)  (directionBitVector |= _BV(stepper))

/**
 * Number of (linear independent) axis for this machine. The number
 * defines the world and axis coordinate system for the machine at hand.
 * Therefore this number shall not be higher than three.
 * Default number of axis is set to three. It's possible to override
 * default in the respective configuration file or by specifying the
 * value during compile time with -MACHINE_NUM_AXIS 3
 * @TODO Move to machine/kinematic module
 */
#ifndef MACHINE_NUM_AXIS
#define MACHINE_NUM_AXIS              (uint8_t)3
#endif

/**
 * Number of extruder for the machine at hand. Default number of extruder
 * is set to one.
 * It's possible to override default in the respective configuration file
 * or by specifying the value during compile time with
 * -DMACHINE_NUM_EXTRUDER 3
 * @TODO Move to machine/kinematic module
 */
#ifndef MACHINE_NUM_EXTRUDER
#define MACHINE_NUM_EXTRUDER          (uint8_t)1
#endif

/* ******************| Type definitions |****************************** */

/* TODO: To be moved to machine/Kinematik module */
typedef float WorldCoordinate_t;
typedef struct {
        WorldCoordinate_t x;    /*!< x coordinate in world coordinate system given in mm */
        WorldCoordinate_t y;    /*!< y coordinate in world coordinate system given in mm */
        WorldCoordinate_t z;    /*!< z coordinate in world coordinate system given in mm */
        WorldCoordinate_t e;    /*!< Extruder coordinates in mm. In contrast to x,y and z coordinates this is always in given in relative coordinates */
} WorldCoordinates_t;

/**
 * Axis coordinate in steps
 */
typedef int32_t AxisCoordinate_t;
/**
 * Axis coordinates in steps calculated from world coordinates using
 * machine's inverse kinematics function including any mechanical related
 * things like
 * - steps per rotation (FULL_STEPS_PER_ROTATION)
 * - micro-steps (MICROSTEPS)
 * - pulley-teeth (PULLEY_TEETH)
 * - belt pitch (BELT_PITCH)
 * - gear-box ratio
 * For Cartesian machines inverse kinematics will mostly be the product of
 * above values for delta and other machine more complicated inverse kinematics
 * need to be applied.
 */
typedef struct {
        AxisCoordinate_t axis[MACHINE_NUM_AXIS];            /*!< Values for all axis in steps. Thus, steps, steps/second, steps/second^2, ... */
        AxisCoordinate_t extruder[MACHINE_NUM_EXTRUDER];    /*!< Values for all available extruder in steps. Thus, steps, steps/second, steps/second^2, .. */
} AxisCoordinates_t;

/*
 * Feedrate, that is speed, in axis coordinates in steps per second.
 * This value is always positive.
 */
typedef uint32_t AxisFeedrate_t;


/**
 * Steps for stepper driver. Steps are always absolute steps plus direction
 * bits. If there is more than one stepper connected to one axis this shall
 * be handled in the respective Stepper module.
 */
typedef uint32_t StepperCoordinate_t;
typedef struct {
        StepperCoordinate_t steps[MACHINE_NUM_AXIS];          /*!< Absolute number of steps for each axis stepper */
        StepperCoordinate_t extruder[MACHINE_NUM_EXTRUDER];   /*!< Absolute number of steps for each extruder stepper */
        uint8_t directionBits;                                /*!< Direction bit-field for each stepper. Bits are used in the same order as axis are defined. */
} StepperCoordinates_t;
/* ******************| External function declarations |**************** */
extern void setup(void);
extern void loop(void);


/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( TEMPLATE_INCLUDE_TEMPLATE_H_ ) */
/* ******************| End of file |*********************************** */
