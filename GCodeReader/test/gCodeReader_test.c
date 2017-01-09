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
#include <string.h>

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */


/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */
/**
 * Simple parse test to see if special fields according to
 * [http://reprap.org/wiki/Gcode#Special_fields] are filtered correctly
 * Test if line numbers are filtered (N: Line number)
 * Test if CRC is filtered (*: Checksum)
 * Test if comments are filtered out completely
 * Test if all blank characters are filtered
 *
 */
static void GCodeReader_GCodeReader_parse_1(void)
{
  char testBuffer[100];

  strcpy(testBuffer, "M119 X0 Y0,0 Z200 \t *200");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("M119X0Y0,0Z200", (char*)testBuffer);

  strcpy(testBuffer, "M119 X0   Y0,0    Z2    E4");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("M119X0Y0,0Z2E4", (char*)testBuffer);

  strcpy(testBuffer, "M119X0Y0,0Z200");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("M119X0Y0,0Z200", (char*)testBuffer);

  strcpy(testBuffer, "N3 T0*57 ; This is a comment");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("T0", (char*)testBuffer);

  strcpy(testBuffer, "N4 G92 E0*67");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("G92E0", (char*)testBuffer);

  strcpy(testBuffer, ";This is a comment");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("", (char*)testBuffer);
}

/**
 * Simple parse test to see if fields according to
 * [http://reprap.org/wiki/Gcode#Fields] are *not* filtered but compressed
 * including their values.
 * Test each of the fields from [http://reprap.org/wiki/Gcode#Fields] with
 * different length of data in different combinations.
 *
 */
static void GCodeReader_GCodeReader_parse_2(void)
{
  char testBuffer[100];

  strcpy(testBuffer, "G100 M119 X0 Y0,0 Z200 \t *200");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("G100M119X0Y0,0Z200", (char*)testBuffer);

  strcpy(testBuffer, "G100 T22 S021 P230 *200");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("G100T22S021P230", (char*)testBuffer);

  /* U,V,W parameter are in the list but not supported and therefore filtered
   * However, all following valid commands should not be filtered. */
  strcpy(testBuffer, "G100 M119 U99.2 V0 W222 F22");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("G100M119F22", (char*)testBuffer);

  strcpy(testBuffer, "I99.2 J0 D222 H7 F99999");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("I99.2J0D222H7F99999", (char*)testBuffer);

  /* Q parameter is also not supported */
  strcpy(testBuffer, "R1 Q119 E88.2 N222");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("R1E88.2", (char*)testBuffer);
}

/**
 * Simple parse test to see if g-code bigger than buffer
 * work
 * Test if g-code commands bigger than buffer are truncated
 * to GCODEREADER_GCODEBUFFER_SIZE
 *
 */
static void GCodeReader_GCodeReader_parse_3(void)
{
  char testBuffer[100];

  strcpy(testBuffer, "G100 M119 T888 S9999.00 X0 Y0,0 Z200 I876.23 J12345.23");
  GCodeReader_addGCode((uint8_t *)testBuffer);
  TEST_ASSERT_EQUAL_STRING("G100M119T888S9999.00X0Y0,0Z200I876.23J1234", (char*)testBuffer);
}

/**
 * Simple parse test to see if CRC check works
 *
 */
static void GCodeReader_GCodeReader_parse_4(void)
{
  char testBuffer[100];

  strcpy(testBuffer, "N6 G1 F1500.0*82");
}

/* Test buffer length */
/* CRC Test */

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
    new_TestFixture("Test case GCodeReader_parse_1", GCodeReader_GCodeReader_parse_1),
    new_TestFixture("Test case GCodeReader_parse_2", GCodeReader_GCodeReader_parse_2),
    new_TestFixture("Test case GCodeReader_parse_3", GCodeReader_GCodeReader_parse_3),
    new_TestFixture("Test case GCodeReader_parse_4", GCodeReader_GCodeReader_parse_4)
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
