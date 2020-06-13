/*
 * drv8388.h
 *
 *  Created on: 9. 6. 2020
 *      Author: janmu
 */

#ifndef DRV8838_DRV8388_H_
#define DRV8838_DRV8388_H_

typedef enum
{
	DRV8838_OK,
	DRV8838_ERROR
} DRV8838_STATUS;

typedef enum
{
	DRV8838_DIR_CW,
	DRV8838_DIR_CCW
} DRV8838_DIR;

DRV8838_STATUS Drv8838_Init(void);
DRV8838_STATUS Drv8838_Start(DRV8838_DIR eDir);
DRV8838_STATUS Drv8838_Stop(void);


#endif /* DRV8838_DRV8388_H_ */
