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
#if (!defined RINGBUFFER_INCLUDE_RINGBUFFER_H_)
/* Preprocessor exclusion definition */
#define RINGBUFFER_INCLUDE_RINGBUFFER_H_
/**
 * Generic ringbuffer template class.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup RingBuffer
 * @{
 */

/* ******************| Inclusions |************************************ */
#include <platform.h>

/* ******************| Macros |**************************************** */
#define RINGBUFFER_LASTOPERATION_READ         FALSE
#define RINGBUFFER_LASTOPERATION_WRITE        TRUE

/* ******************| Type definitions |****************************** */

/* Some function like macro to make code more readable */
#define RingBuffer_incrementIndex(a)          a = ((a + 1) % ringBufferSize)
#define RingBuffer_decrementIndex(a)          a = (((RingBuffer_BufferIndex_t)(a - 1)) % ringBufferSize)
#define RingBuffer_ringBufferFull(x)          (x.lastOperation == RINGBUFFER_LASTOPERATION_WRITE && (x.head == x.tail))
#define RingBuffer_ringBufferEmpty(x)         (x.lastOperation == RINGBUFFER_LASTOPERATION_READ && (x.head == x.tail))


template <class T, uint8_t ringBufferSize> class RingBuffer
{

    /**
     * Datatype to keep track of last operation to ring buffer. FALSE if last
     * operation was a read, otherwise last operation was a write to buffer
     */
    typedef bool RingBuffer_lastOperation_t;


    /**
     * Typedef for head and tail pointer of ringbuffer
     */
    typedef uint8_t RingBuffer_BufferIndex_t;

    /**
    * Data structure for ring buffer.
    * Index pointer for head and tail will always point to element which is next to be read/written.
    * This ring buffer will use "Record last operation" for full/empty buffer distinction see
    * https://en.wikipedia.org/wiki/Circular_buffer "Record last operation" for details
    */
    typedef struct
    {
        T buffer[ringBufferSize];                  /*!< Content of ring buffer */
        RingBuffer_BufferIndex_t head;             /*!< Index for writing to the ring buffer. Index is increased after writing (i.e. producing) an element */
        RingBuffer_BufferIndex_t tail;             /*!< Index for reading from ring buffer. Index is increased after reading (i.e consuming) an element. */
        RingBuffer_lastOperation_t lastOperation;  /*!< False if last operation was reading the buffer, true if last operation was writting into the buffer */
    } RingBuffer_RingBuffer_t;

private:
    RingBuffer_RingBuffer_t ringBuffer;
    RingBuffer_BufferIndex_t iterator;             /*!< Iterator used to iterate over the buffer without consuming elements */
  
public:
    RingBuffer();
    uint8_t write(T data);
    uint8_t read(T *data);
    uint8_t available();

    T* startIterator();
    T* nextElement();
    T* previousElement();
};

/* ******************| External function declarations |**************** */

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( RINGBUFFER_INCLUDE_RINGBUFFER_H_ ) */
/* ******************| End of file |*********************************** */
