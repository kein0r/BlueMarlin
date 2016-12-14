/**
 * \file gCodeRingBuffer_test_drv.c
 *
 * \brief GCodeRingBuffer unit test implementation
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
//#include <gCodeRingBuffer.cpp>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */
int TemplateTest_templateFunction(int i, int *s);

/* ******************| Global Variables |****************************** */


/* ******************| Function Implementation |*********************** */

static void GCodeRingBuffer_GCodeRingBuffer_1(void)
{
  TEST_ASSERT(1);
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

TestRef GCodeRingBuffer_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case GCodeRingBuffer_GCodeRingBuffer_1", GCodeRingBuffer_GCodeRingBuffer_1)
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
