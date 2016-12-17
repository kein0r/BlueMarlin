/**
 * \file gCodeRingBuffer_test_drv.c
 *
 * \brief GCodeRingBuffer unit test implementation
 *
 * Please see http://embunit.sourceforge.net/ for more information. For 
 * detailed documentation see http://embunit.sourceforge.net/embunit/index.html
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup GCodeRingBuffer
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "gCodeRingBuffer_test.h"
/* Include .cpp file to be tested in order to get access to all private
 * or static functions */
#define UNIT_TEST
#include <gCodeRingBuffer.cpp>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */
int TemplateTest_templateFunction(int i, int *s);

/* ******************| Global Variables |****************************** */
GCodeRingBuffer *gCodeRingBuffer;


/* ******************| Function Implementation |*********************** */

/*
 * This test will make sure that after initialization buffer is empty.
 */
static void GCodeRingBuffer_GCodeRingBuffer_Init_1(void)
{
  TEST_ASSERT_EQUAL_INT(0, gCodeRingBuffer->available());
}

/*
 * Test if reading an element from an empty buffer will return RESULT_NOT_OK
 */
static void GCodeRingBuffer_GCodeRingBuffer_Read_1(void)
{
  GCodeRingBuffer_gCode_t element;
  /* Try to read one element from empty ringbuffer */
  TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, gCodeRingBuffer->read(&element));
}

/*
 * Insert one element to the ringbuffer 
 * Test if the ringbuffer will contain this element
 * Read the element back from rinbuffer and check if return value is 
 * RESULT_OK
 * Test if ringbuffer is empty afterwards
 */
static void GCodeRingBuffer_GCodeRingBuffer_Read_2(void)
{
  GCodeRingBuffer_gCode_t element = 0xaa;
  /* Insert on random element in empty ringbuffer */
  gCodeRingBuffer->write(element);
  /* Check if ringbuffer now contains exactly one element */
  TEST_ASSERT_EQUAL_INT(1, gCodeRingBuffer->available());
  /* Remove the element again and check if RESULT_OK is returned */
  TEST_ASSERT_EQUAL_INT(RESULT_OK, gCodeRingBuffer->read(&element));
  /* Make sure ringbuffer is empty again */
  TEST_ASSERT_EQUAL_INT(0, gCodeRingBuffer->available());
}

/*
 * Insert a few elements in the buffer
 * Test if return value is RESULT_OK when buffer is not full
 * Test if return value is RESULT_NOT_OK when buffer is full
 */
static void GCodeRingBuffer_GCodeRingBuffer_Write_1(void)
{
  GCodeRingBuffer_gCode_t element = 0xaa;
  for (int i=0; i<GCODERINGBUFFER_RINGBUFFER_SIZE; i++)
  {
	element = (GCodeRingBuffer_gCode_t)i;
	TEST_ASSERT_EQUAL_INT(i, gCodeRingBuffer->available());
    TEST_ASSERT_EQUAL_INT(RESULT_OK, gCodeRingBuffer->write(element));
  }
  /* Ringbuffer is full now, check if another write will return
   * RESULT_NOT_OK */
   TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, gCodeRingBuffer->write(element));
}

/**
 * Test Setup function which is called before all each test case
 */
static void setUp(void)
{
	gCodeRingBuffer = new GCodeRingBuffer();
}

/**
 * Test Teardown function which is called for after each test
 */
static void tearDown(void)
{
	delete(gCodeRingBuffer);
}

TestRef GCodeRingBuffer_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case GCodeRingBuffer_GCodeRingBuffer_Init_1", GCodeRingBuffer_GCodeRingBuffer_Init_1),
	new_TestFixture("Test case GCodeRingBuffer_GCodeRingBuffer_Read_1", GCodeRingBuffer_GCodeRingBuffer_Read_1),
	new_TestFixture("Test case GCodeRingBuffer_GCodeRingBuffer_Read_2", GCodeRingBuffer_GCodeRingBuffer_Read_2),
	new_TestFixture("Test case GCodeRingBuffer_GCodeRingBuffer_Write_1", GCodeRingBuffer_GCodeRingBuffer_Write_1)
  };
  EMB_UNIT_TESTCALLER(GCodeRingBuffer_tests,"GCodeRingBuffer Unit test",setUp,tearDown,fixtures);
  return (TestRef)&GCodeRingBuffer_tests;
}

/**
 *
 */
int main(void)
{
  TestRunner_start();
  TestRunner_runTest(GCodeRingBuffer_test_RunTests());
  TestRunner_end();
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */