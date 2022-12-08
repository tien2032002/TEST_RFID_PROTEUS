/*
 * integer.h
 *
 *  Created on: Nov 25, 2022
 *      Author: Administrator
 */

#ifndef INC_INTEGER_H_
#define INC_INTEGER_H_

/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/


#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char    BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;


#endif

#endif /* INC_INTEGER_H_ */
