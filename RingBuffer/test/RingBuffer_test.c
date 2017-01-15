/**
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
#include "RingBuffer_test.h"
#include "stdio.h"
/* Include .cpp file to be tested in order to get access to all private
 * or static functions */

#include "../src/ringBuffer.cpp"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */
typedef struct {
	uint8_t a;
	uint16_t b;
	uint32_t c;
	float d;
} testStruct_t;

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */
RingBuffer<char, RINGBUFFER_RINGBUFFER_TESTSIZE> *charRingBuffer;
RingBuffer<testStruct_t, RINGBUFFER_RINGBUFFER_TESTSIZE> *structRingBuffer;


/* ******************| Function Implementation |*********************** */

/*
 * This test will make sure that after initialization buffer is empty.
 */
static void RingBuffer_RingBuffer_InitChar_1(void)
{
  TEST_ASSERT_EQUAL_INT(0, charRingBuffer->available());
}

/*
 * Test if reading an element from an empty buffer will return RESULT_NOT_OK
 */
static void RingBuffer_RingBuffer_ReadChar_1(void)
{
  char element;
  /* Try to read one element from empty ringbuffer */
  TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, charRingBuffer->read(&element));
}

/*
 * Insert one element to the ringbuffer 
 * Test if the ringbuffer will contain this element
 * Read the element back from rinbuffer and check if return value is 
 * RESULT_OK
 * Test if ringbuffer is empty afterwards
 */
static void RingBuffer_RingBuffer_ReadChar_2(void)
{
  char element = 0xaa;
  /* Insert on random element in empty ringbuffer */
  charRingBuffer->write(element);
  /* Check if ringbuffer now contains exactly one element */
  TEST_ASSERT_EQUAL_INT(1, charRingBuffer->available());
  /* Remove the element again and check if RESULT_OK is returned */
  TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->read(&element));
  /* Make sure ringbuffer is empty again */
  TEST_ASSERT_EQUAL_INT(0, charRingBuffer->available());
}

/**
 * Simple write test writing a few elements to ringbuffer 
 * Test if rinbuffer is empty
 * Write two elements
 * Test if ringbuffer fill rate is reported correctly
 * Read back both elements
 * Test if value is the same as written
 * Test if ringbuffer is empty again
 */
static void RingBuffer_RingBuffer_WriteChar_1(void)
{
  /* Write two elements to rinbuffer */
  char element = 0xaa;
  TEST_ASSERT_EQUAL_INT(0, charRingBuffer->available());
  TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->write(element));
  TEST_ASSERT_EQUAL_INT(1, charRingBuffer->available());
  element = 0xbb;
  TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->write(element));
  TEST_ASSERT_EQUAL_INT(2, charRingBuffer->available());
  
  /* Readback first element from buffer and check its value */
  TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->read(&element));
  TEST_ASSERT_EQUAL_INT((char)0xaa, element);
  
  /* Readback first element from buffer and check its value */
  TEST_ASSERT_EQUAL_INT(1, charRingBuffer->available());
  TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->read(&element));
  TEST_ASSERT_EQUAL_INT((char)0xbb, element);
  
  /* Check if buffer is empty again */
  TEST_ASSERT_EQUAL_INT(0, charRingBuffer->available());
}

/**
 * Insert more elements than the ringbuffer can hold
 * Test if return value is RESULT_OK when buffer is not full
 * Test if buffer fill rate is reported correctly
 * Test if return value is RESULT_NOT_OK when buffer is full
 * Read the elements back
 * Test if buffer fill rate is reported correctly
 * Test if value can be read back correctly
 * Test if read returns RESULT_OK as long as ringbuffer contains values
 * Test if read returns RESULT_NOT_OK if buffer is empty again
 */
static void RingBuffer_RingBuffer_WriteChar_2(void)
{
  char element = 0xaa;
  for (int i=0; i<RINGBUFFER_RINGBUFFER_TESTSIZE; i++)
  {
    element = (char)i;
    TEST_ASSERT_EQUAL_INT(i, charRingBuffer->available());
    TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->write(element));
  }
  /* Ringbuffer is full now, check if another write will return
   * RESULT_NOT_OK */
   TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, charRingBuffer->write(element));
   
  /* Check if values can be read back correctly and in the same sequence */
  for (int i=0; i<RINGBUFFER_RINGBUFFER_TESTSIZE; i++)
  {
    TEST_ASSERT_EQUAL_INT(RINGBUFFER_RINGBUFFER_TESTSIZE-i, charRingBuffer->available());
    element = 0xaa;
    TEST_ASSERT_EQUAL_INT(RESULT_OK, charRingBuffer->read(&element));
    TEST_ASSERT_EQUAL_INT(i, element);
  }
  TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, charRingBuffer->read(&element));
}


/*
 * This test will make sure that after initialization buffer is empty.
 */
static void RingBuffer_RingBuffer_InitStruct_1(void)
{
  TEST_ASSERT_EQUAL_INT(0, structRingBuffer->available());
}

/*
 * Test if reading an element from an empty buffer will return RESULT_NOT_OK
 */
static void RingBuffer_RingBuffer_ReadStruct_1(void)
{
  testStruct_t element;
  /* Try to read one element from empty ringbuffer */
  TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, structRingBuffer->read(&element));
}

/*
 * Insert one element to the ringbuffer
 * Test if the ringbuffer will contain this element
 * Read the element back from rinbuffer and check if return value is
 * RESULT_OK
 * Test if ringbuffer is empty afterwards
 */
static void RingBuffer_RingBuffer_ReadStruct_2(void)
{
  testStruct_t element = {0x11, 0x2233, 0x44556677, 8.888};
  /* Insert on random element in empty ringbuffer */
  structRingBuffer->write(element);
  /* Check if ringbuffer now contains exactly one element */
  TEST_ASSERT_EQUAL_INT(1, structRingBuffer->available());
  /* Remove the element again and check if RESULT_OK is returned */
  TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->read(&element));
  /* Make sure ringbuffer is empty again */
  TEST_ASSERT_EQUAL_INT(0, structRingBuffer->available());
}

/**
 * Simple write test writing a few elements to ringbuffer
 * Test if rinbuffer is empty
 * Write two elements
 * Test if ringbuffer fill rate is reported correctly
 * Read back both elements
 * Test if value is the same as written
 * Test if ringbuffer is empty again
 */
static void RingBuffer_RingBuffer_WriteStruct_1(void)
{
  /* Write two elements to rinbuffer */
  testStruct_t element = {0x11, 0x2233, 0x44556677, 8.888};
  TEST_ASSERT_EQUAL_INT(0, structRingBuffer->available());
  TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->write(element));
  TEST_ASSERT_EQUAL_INT(1, structRingBuffer->available());
  element = {0x88, 0x99aa, 0xbbccddee, 9.999};
  TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->write(element));
  TEST_ASSERT_EQUAL_INT(2, structRingBuffer->available());

  /* Readback first element from buffer and check its value */
  element = {0x00, 0x00, 0x00, 0.0};
  TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->read(&element));
  TEST_ASSERT_EQUAL_INT((unsigned) 0x11, element.a);
  TEST_ASSERT_EQUAL_INT((unsigned) 0x2233, element.b);
  TEST_ASSERT_EQUAL_INT((unsigned) 0x44556677, element.c);
  TEST_ASSERT((float)8.888 == element.d);

  /* Readback second element from buffer and check its value */
  TEST_ASSERT_EQUAL_INT(1, structRingBuffer->available());
  TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->read(&element));
  TEST_ASSERT_EQUAL_INT((unsigned)0x88, element.a);
  TEST_ASSERT_EQUAL_INT((unsigned)0x99aa, element.b);
  TEST_ASSERT_EQUAL_INT((unsigned)0xbbccddee, element.c);
  TEST_ASSERT((float)9.999 == element.d);

  /* Check if buffer is empty again */
  TEST_ASSERT_EQUAL_INT(0, structRingBuffer->available());
}

/**
 * Insert more elements than the ringbuffer can hold
 * Test if return value is RESULT_OK when buffer is not full
 * Test if buffer fill rate is reported correctly
 * Test if return value is RESULT_NOT_OK when buffer is full
 * Read the elements back
 * Test if buffer fill rate is reported correctly
 * Test if value can be read back correctly
 * Test if read returns RESULT_OK as long as ringbuffer contains values
 * Test if read returns RESULT_NOT_OK if buffer is empty again
 */
static void RingBuffer_RingBuffer_WriteStruct_2(void)
{
  testStruct_t element = {0x11, 0x2233, 0x44556677, 8.888};
  for (int i=0; i<RINGBUFFER_RINGBUFFER_TESTSIZE; i++)
  {
	element.a = i;
	element.b = i;
	element.c = i;
	element.d = i;
    TEST_ASSERT_EQUAL_INT(i, structRingBuffer->available());
    TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->write(element));
  }
  /* Ringbuffer is full now, check if another write will return
   * RESULT_NOT_OK */
   TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, structRingBuffer->write(element));

  /* Check if values can be read back correctly and in the same sequence */
  for (int i=0; i<RINGBUFFER_RINGBUFFER_TESTSIZE; i++)
  {
    TEST_ASSERT_EQUAL_INT(RINGBUFFER_RINGBUFFER_TESTSIZE-i, structRingBuffer->available());
    element = {0x11, 0x2233, 0x44556677, 8.888};
    TEST_ASSERT_EQUAL_INT(RESULT_OK, structRingBuffer->read(&element));
    TEST_ASSERT_EQUAL_INT((unsigned)i, element.a);
    TEST_ASSERT_EQUAL_INT((unsigned)i, element.b);
    TEST_ASSERT_EQUAL_INT((unsigned)i, element.c);
    TEST_ASSERT_EQUAL_INT(i, element.d);
  }
  TEST_ASSERT_EQUAL_INT(RESULT_NOT_OK, structRingBuffer->read(&element));
}

/**
 * Test Setup function which is called before all each test case
 */
static void setUpCharRingBuffer(void)
{
	charRingBuffer = new RingBuffer<char, RINGBUFFER_RINGBUFFER_TESTSIZE>();
}

/**
 * Test Teardown function which is called for after each test
 */
static void tearDownCharRingBuffer(void)
{
  delete(charRingBuffer);
}

/**
 * Test Setup function which is called before all each test case
 */
static void setUpStructRingBuffer(void)
{
	structRingBuffer = new RingBuffer<testStruct_t, RINGBUFFER_RINGBUFFER_TESTSIZE>();
}

/**
 * Test Teardown function which is called for after each test
 */
static void tearDownStructRingBuffer(void)
{
  delete(structRingBuffer);
}

TestRef CharRingBuffer_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case RingBuffer_RingBuffer_Init_1", RingBuffer_RingBuffer_InitChar_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_ReadChar_1", RingBuffer_RingBuffer_ReadChar_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_ReadChar_2", RingBuffer_RingBuffer_ReadChar_2),
    new_TestFixture("Test case RingBuffer_RingBuffer_WriteChar_1", RingBuffer_RingBuffer_WriteChar_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_WriteChar_2", RingBuffer_RingBuffer_WriteChar_2)
  };
  EMB_UNIT_TESTCALLER(CharRingBuffer_tests,"GCodeRingBuffer Unit test",setUpCharRingBuffer,tearDownCharRingBuffer,fixtures);
  return (TestRef)&CharRingBuffer_tests;
}

TestRef StructRingBuffer_test_RunTests(void)
{
  EMB_UNIT_TESTFIXTURES(fixtures) {
    new_TestFixture("Test case RingBuffer_RingBuffer_Init_1", RingBuffer_RingBuffer_InitStruct_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_ReadStruct_1", RingBuffer_RingBuffer_ReadStruct_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_ReadStruct_2", RingBuffer_RingBuffer_ReadStruct_2),
    new_TestFixture("Test case RingBuffer_RingBuffer_WriteStruct_1", RingBuffer_RingBuffer_WriteStruct_1),
    new_TestFixture("Test case RingBuffer_RingBuffer_WriteStruct_2", RingBuffer_RingBuffer_WriteStruct_2)
  };
  EMB_UNIT_TESTCALLER(CharRingBuffer_tests,"GCodeRingBuffer Unit test",setUpStructRingBuffer,tearDownStructRingBuffer,fixtures);
  return (TestRef)&CharRingBuffer_tests;
}

/**
 *
 */
int main(void)
{
  TestRunner_start();
  TestRunner_runTest(CharRingBuffer_test_RunTests());
  TestRunner_runTest(StructRingBuffer_test_RunTests());
  TestRunner_end();
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
