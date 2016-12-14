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
#if (!defined GCODERINGBUFFER_INCLUDE_GCODERINGBUFFER_H_)
/* Preprocessor exclusion definition */
#define GCODERINGBUFFER_INCLUDE_GCODERINGBUFFER_H_
/**
 * \file GCodeRingBuffer.h
 *
 * \brief GCodeRingBuffer include file
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup GCodeRingBuffer
 * @{
 */

/* ******************| Inclusions |************************************ */
#include <platform.h>

/* ******************| Macros |**************************************** */
#ifndef GCODERINGBUFFER_RINGBUFFER_SIZE
/**
 * Default number of entries in ringbuffer. Its possible to override default 
 * value for GCODERINGBUFFER_RINGBUFFER_SIZE via configuration.h or compiler
 * by using -DGCODERINGBUFFER_RINGBUFFER_SIZE=32
 * @note: Due to the way empty available bytes are calculated, 
 * GCODERINGBUFFER_RINGBUFFER_SIZE must be always to the power of two.
 */
#define GCODERINGBUFFER_RINGBUFFER_SIZE      (uint8_t)32
#endif

/* ******************| Type definitions |****************************** */
/**
 * GCode buffer data. 
 */
typedef uint8_t GCodeRingBuffer_gCode_t;

/**
 * Typedef for head and tail pointer of ringbuffer
 */
typedef uint8_t GCodeRingBuffer_BufferIndex_t;

/**
 * Datatype to keep track of last operation to ring buffer. FALSE if last 
 * operation was a read, otherwise last operation was a write to buffer 
 */
typedef bool GCodeRingBuffer_lastOperation_t; 
#define GCODERINGBUFFER_LASTOPERATION_READ         FALSE
#define GCODERINGBUFFER_LASTOPERATION_WRITE        TRUE

/**
 * Data structure for ring buffer.
 * Index pointer for head and tail will always point to element which is next to be read/written.
 * This ring buffer will use "Record last operation" for full/empty buffer distinction see
 * https://en.wikipedia.org/wiki/Circular_buffer "Record last operation" for details
 */
typedef struct
{
  GCodeRingBuffer_gCode_t buffer[GCODERINGBUFFER_RINGBUFFER_SIZE];  /*!< Content of ring buffer */
  GCodeRingBuffer_BufferIndex_t head;                               /*!< Index for writing to the ring buffer. Index is increased after writing (i.e. producing) an element */
  GCodeRingBuffer_BufferIndex_t tail;                               /*!< Index for reading from ring buffer. Index is increased after reading (i.e consuming) an element. */
  GCodeRingBuffer_lastOperation_t lastOperation;                    /*!< False if last operation was reading the buffer, true if last operation was writting into the buffer */
} GCodeRingBuffer_RingBuffer_t;
/* Some function like macro to make code more readable */
#define GCodeRingBuffer_incrementIndex(a)          a = (a + 1) % GCODERINGBUFFER_RINGBUFFER_SIZE
#define GCodeRingBuffer_ringBufferFull(x)          (x.lastOperation == GCODERINGBUFFER_LASTOPERATION_WRITE && (x.head == x.tail))
#define GCodeRingBuffer_ringBufferEmpty(x)         (x.lastOperation == GCODERINGBUFFER_LASTOPERATION_READ && (x.head == x.tail))


class GCodeRingBuffer
{
private:
  GCodeRingBuffer_RingBuffer_t gCodeRingBuffer_RingBuffer;
  
public:
  GCodeRingBuffer();
  uint8_t write(GCodeRingBuffer_gCode_t data);
  uint8_t read(GCodeRingBuffer_BufferIndex_t *data);
  uint8_t available();
};

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( GCODERINGBUFFER_INCLUDE_GCODERINGBUFFER_H_ ) */
/* ******************| End of file |*********************************** */
