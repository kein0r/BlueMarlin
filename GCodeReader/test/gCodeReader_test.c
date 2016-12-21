/**
 * \file gCodeReader_test.c
 *
 * \brief GCodeReader unit test implementation
 *
 * Please see http://embunit.sourceforge.net/ for more information. For
 * detailed documentation see http://embunit.sourceforge.net/embunit/index.html
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */


/** \addtogroup GCodeReader
 * @{
 */

/* ******************| Inclusions |************************************ */
#include "gCodeReader_test.h"
/* Include .cpp file to be tested in order to get access to all private
 * or static functions */
#include <gCodeReader.cpp>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */


/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */
/**
 * Simple write test writing a few elements to ringbuffer
 * Test if rinbuffer is empty
 * Write two elements
 * Test if ringbuffer fill rate is reported correctly
 * Read back both elements
 * Test if value is the same as written
 * Test if ringbuffer is empty again
 */
static void GCodeReader_parse_1(void)
{
}

/**
 * Test Setup function which is called before all each test case
 */
static void setUp(void)
{

}

/**
 * Test Teardown function which is called for after each test
 */
static void tearDown(void)
{

}

TestRef GCodeReader_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case GCodeReader_parse_1", GCodeReader_parse_1)
  };
  EMB_UNIT_TESTCALLER(GCodeReader_tests,"GCodeRingBuffer Unit test",setUp,tearDown,fixtures);
  return (TestRef)&GCodeReader_tests;
}

/**
 *
 */
int main(void)
{
  TestRunner_start();
  TestRunner_runTest(GCodeReader_test_RunTests());
  TestRunner_end();
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
