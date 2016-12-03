#if (!defined PLATFORM_INCLUDE_TEMPLATE_H_)
/* Preprocessor exclusion definition */
#define PLATFORM_INCLUDE_TEMPLATE_H_
/**
 * \file platform.h
 *
 * \brief Platform module include file
 *
 * The inclusion protection does not obey the naming because there shall
 * be only one platform used at a time.
 *
 * \project BlueMarlin
 * \author kein0r
 *
 */
/** \addtogroup Platform_WindowsX86
 * @{
 */

/* ******************| Inclusions |************************************ */

/* ******************| Macros |**************************************** */

/* ******************| Type definitions |****************************** */

/* ******************| External function declarations |**************** */
void init(void);
void loop(void);

/* ******************| External constants |**************************** */

/* ******************| External variables |**************************** */

/** @} doxygen end group definition */
#endif /* if !defined( PLATFORM_INCLUDE_TEMPLATE_H_ ) */
/* ******************| End of file |*********************************** */
