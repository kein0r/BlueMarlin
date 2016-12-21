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
 * Test Teardown function which is called for after each test
 */
static void tearDown(void)
{

}

TestRef GCodeRingBuffer_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case GCodeReader_parse_1", GCodeReader_parse_1)
  };
  EMB_UNIT_TESTCALLER(GCodeReader_test_RunTests,"GCodeRingBuffer Unit test",setUp,tearDown,fixtures);
  return (TestRef)&GCodeReader_test_RunTests;
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
