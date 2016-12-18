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
 * \file gCodeRingBuffer.c
 *
 * \brief Ring buffer for g codes
 *
 * Implementation of a ring buffer for g-codes. 
 *
 * @note This replaces the following functions 
 * - drain_queued_commands_P: Reads commands from RAM placed there by other parts of the program
 * - enqueue_and_echo_command: Copies command from RAM to intermediate global buffer
 * - _enqueuecommand: Copies command to command_queue buffer 
 * - _commit_command: Moves the write pointer of command_queue (cmd_queue_index_w) ahead
 * 
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup GCodeRingBuffer
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "gCodeRingBuffer.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

/**
 * Initializes GCodeRingBuffer module.
 */
GCodeRingBuffer::GCodeRingBuffer(void)
{
  /* Initialize ring buffer */
  ringBuffer.head = 0;
  ringBuffer.tail = 0;
  ringBuffer.lastOperation = GCODERINGBUFFER_LASTOPERATION_READ; /* Buffer is empty on start-up */
}

/**
 * Write one element to ringbuffer. Element will be appended to the existing
 * data. If buffer is full no data will be written and function returns 
 * RESULT_NOT_OK.
 * @param data data to be written to ringbuffer
 * @return Returns RESULT_OK in case element could be added to ringbuffer, 
 * RESULT_NOT_OK if not
 * @note This function is non-blocking. If the element can't be added
 * the function will just return.
 */
uint8_t GCodeRingBuffer::write(const GCodeRingBuffer_BufferIndex_t data)
{
  uint8_t retVal = RESULT_NOT_OK;
  if (!GCodeRingBuffer_ringBufferFull(ringBuffer))
  {
    /* Place data in buffer */
    ringBuffer.buffer[ringBuffer.head] = data;
    ringBuffer.lastOperation = GCODERINGBUFFER_LASTOPERATION_WRITE;
    GCodeRingBuffer_incrementIndex(ringBuffer.head);
	retVal = RESULT_OK;
  }
  else
  {
    /* Nothing to be done */
  }
  return retVal;
}

/**
 * Returns one element from ringbuffer and removes it from ringbuffer. It
 * is suggested to call #available before calling this function to check 
 * data is present in buffer.
 * @return Next  from rx ring buffer or 0x00 if no byte was in buffer
 * @param data If data is available in ringbuffer it will be copied here.
 * If no data is present #data will be left untouched.
 * @return Function will return RESULT_OK in case data was present in 
 * ringbuffer and was copied to #data. RESULT_NOT_OK if not.
 */
uint8_t GCodeRingBuffer::read(GCodeRingBuffer_BufferIndex_t *data)
{
  uint8_t retVal = RESULT_NOT_OK;
  
  if(! GCodeRingBuffer_ringBufferEmpty(ringBuffer) )
  {
    *data = ringBuffer.buffer[ringBuffer.tail];
    ringBuffer.lastOperation = GCODERINGBUFFER_LASTOPERATION_READ;
    GCodeRingBuffer_incrementIndex(ringBuffer.tail);
	retVal = RESULT_OK;
  }
  return retVal;
}

/**
 * \brief Returns the number of bytes in ringbuffer.
 * @return Number of bytes already received from two wire slave device
 * @note This function is not interrupt save in case buffer is filled within
 * interrupt context head must be either copied to a local variable or 
 * interrupts shall be locked before calling (noInterrupts()/interrupts())
 */
uint8_t GCodeRingBuffer::available()
{
  /* Cast to uint8_t is important here because if not compiler will chose sint8_t */
  uint8_t retVal = (uint8_t)(ringBuffer.head - ringBuffer.tail) % GCODERINGBUFFER_RINGBUFFER_SIZE;
  if ((retVal == 0) && (ringBuffer.lastOperation == GCODERINGBUFFER_LASTOPERATION_WRITE))
  {
	retVal = GCODERINGBUFFER_RINGBUFFER_SIZE;
  }
  return retVal;
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
