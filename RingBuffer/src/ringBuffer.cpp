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
 * \brief Generic ringbuffer template class
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


/** \addtogroup RingBuffer
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "ringBuffer.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

/**
 * Initializes RingBuffer module.
 */
template <class T, uint8_t ringBufferSize>RingBuffer<T, ringBufferSize>::RingBuffer()
{
	static_assert(!(ringBufferSize && ((ringBufferSize & (ringBufferSize-1)))), "ringBufferSize must be to the power of two (2, 4, 16, 32, ...)");
    /* Initialize ring buffer */
    ringBuffer.head = 0;
    ringBuffer.tail = 0;
    iterator = ringBufferSize;     /* Set iterator outside of the buffer to mark it invalid */
    ringBuffer.lastOperation = RINGBUFFER_LASTOPERATION_READ; /* Buffer is empty on start-up */
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
template <class T, uint8_t ringBufferSize>uint8_t RingBuffer<T, ringBufferSize>::write(const T data)
{
  uint8_t retVal = RESULT_NOT_OK;
  if (!RingBuffer_ringBufferFull(ringBuffer))
  {
    /* Place data in buffer */
    ringBuffer.buffer[ringBuffer.head] = data;
    ringBuffer.lastOperation = RINGBUFFER_LASTOPERATION_WRITE;
    RingBuffer_incrementIndex(ringBuffer.head);
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
template <class T, uint8_t ringBufferSize> uint8_t RingBuffer<T, ringBufferSize>::read(T *data)
{
  uint8_t retVal = RESULT_NOT_OK;
  
  if(! RingBuffer_ringBufferEmpty(ringBuffer) )
  {
    *data = ringBuffer.buffer[ringBuffer.tail];
    ringBuffer.lastOperation = RINGBUFFER_LASTOPERATION_READ;
    RingBuffer_incrementIndex(ringBuffer.tail);
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
template <class T, uint8_t ringBufferSize> uint8_t RingBuffer<T, ringBufferSize>::available()
{
  /* Cast to uint8_t is important here because if not compiler will chose sint8_t */
  uint8_t retVal = (uint8_t)(ringBuffer.head - ringBuffer.tail) % ringBufferSize;
  if ((retVal == 0) && (ringBuffer.lastOperation == RINGBUFFER_LASTOPERATION_WRITE))
  {
	retVal = ringBufferSize;
  }
  return retVal;
}

/**
 * Initializes the iterator for the rinbuffer. The Iterator is initialized to the first valid
 * element, which is where tail is pointing to. The content of this element is returned.
 * The function must be called before the iterator is accessed and every time the iterator
 * needs to be initialized again.
 * @return Element of ringbuffer to which the newly initialized iterator is pointing to or NULL
 * if ringbuffer is empty.
 * @note While the iterator is in use access to the ringbuffer shall be avoided. Reading the
 * ringbuffer is less critical, however, write could cause unpredictable results.
 */
template <class T, uint8_t ringBufferSize> T* RingBuffer<T, ringBufferSize>::startIterator()
{
  T *retVal = NULL;

  /* We can only iterate over the buffer if it's not empty */
  if (!RingBuffer_ringBufferEmpty(ringBuffer))
  {
    iterator = ringBuffer.tail;
    retVal = &(ringBuffer.buffer[iterator]);
  }
  return retVal;
}

/**
 * Sets (increases) the #iterator to next element, if available, and returns this element.
 * The element is not consumed from the buffer.
 * @return Next element in the ringbuffer or NULL if there is no such element.
 * @pre #startIterator was called to initialize the iterator and return value was not NULL
 */
template <class T, uint8_t ringBufferSize> T* RingBuffer<T, ringBufferSize>::nextElement()
{
  T *retVal = NULL;
  RingBuffer_BufferIndex_t tempIterator = iterator;

  /* Firstly only increment a copy of the real iterator to check if
   * it is not increased beyond head.
   */
  RingBuffer_incrementIndex(tempIterator);

  /* Only increment if we are not yet at head */
  if (tempIterator != ringBuffer.head)
  {
    retVal = &(ringBuffer.buffer[iterator]);
    iterator = tempIterator;
  }
  return retVal;
}

/**
 * Sets (decreases) the #iterator to the previous element and returns this element.
 * The element is not consumed from the buffer.
 * @return Previous element in the ringubffer or NULL if there is no such element.
 * @pre #startIterator was called to initialize the iterator and return value was not NULL
 */
template <class T, uint8_t ringBufferSize> T* RingBuffer<T, ringBufferSize>::previousElement()
{
  T *retVal = NULL;
  /* Only decrement if we are not yet at tail */
  if (iterator != ringBuffer.tail)
  {
    RingBuffer_decrementIndex(iterator);
    retVal = &(ringBuffer.buffer[iterator]);
  }
  return retVal;
}
/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
