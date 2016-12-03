/**
 * \file main.c
 *
 * \brief Template source file
 *
 * File names should start with lowercase character and use cammelCase 
 * notation.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */

/** \addtogroup Platform_WindowsX86
 * @{
 */

/* ******************| Inclusions |************************************ */
#include <time.h>
#include "platform.h"

/* ******************| Macros |**************************************** */

/* ******************| Type Definitions |****************************** */

/* ******************| Function Prototypes |*************************** */

/* ******************| Global Variables |****************************** */

/* ******************| Function Implementation |*********************** */

/*
 * \brief main function to be implemented by each platform
 *
 * The main purpose of the main function will be to trigger the loop init and loop 
 * functions known from Aruduino framework.
 * As this is the main function it obviously does not use the existing naming
 * conventions.
 *
 * @return return value to Os
 */
int main()
{
  /* Call init function normally used by Aurduino framework */
  init();

  /* enter forever loop */
  while (1)
  {
    loop();
  }
  return 0;
}

/** @} doxygen end group definition */
/* ******************| End of file |*********************************** */
