/****************************************************************************
 *   $Id:: target_config.h 4832 2010-09-07 23:04:21Z nxp21346                 $
 *   Project: LED flashing / ISP test program
 *
 *   Description:
 *     This file contains the config settings for the blinky code sample
 *     which flashes an LED on the LPCXpresso board and also increments an
 *     LED display on the Embedded Artists base board. This project
 *     implements CRP and is useful for testing bootloaders.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/

#define BURSTMODE_PORT 		1
#define BURSTMODE_PIN 		5
#define CAN_EN_PORT 		0
#define CAN_EN_PIN 		3
#define DISCHARGE_PORT 		0
#define DISCHARGE_PIN 		6
#define VOLT_SENSE_EN_PORT 	0
#define VOLT_SENSE_EN_PIN 	7
#define TEMP_SENSE_EN_PORT	3
#define TEMP_SENSE_EN_PIN	0
#define ID_PORT			2
#define ID0_PIN			0
#define ID1_PIN			1
#define ID2_PIN			2
#define ID3_PIN			3
#define ID4_PIN			4
#define ID5_PIN			5
#define ORANGE_LED_PORT 	2
#define ORANGE_LED_PIN 		11
#define RED_LED_PORT		2
#define RED_LED_PIN		10
#define WAKEUP_PORT		1
#define WAKEUP_PIN		4
#define VOLT_SENSE_PORT		0
#define VOLT_SENSE_PIN		11
#define TEMP_SENSE_PORT		1
#define TEMP_SENSE_PIN		0
#define INPUT			0
#define OUTPUT			1
#define ADC_VOLT		0
#define ADC_TEMP		1
#define ADC_CALB		2

#define OFF			0
#define ON			1
//#define TRUE			1
//#define FALSE			0

//mode
#define VOLTAGE			1
#define TIME			2



//Set output and input GPIOs
//GPIOSetDir
//
//1.5  -burstmode
//0.3 CAN_en
//0.6 Discharge
//0.7 Volt sense en
//3.0 Temp sense en

//2.0 ID0
//2.1 ID1
//2.2 ID2
//2.3 ID3
//2.4 ID4
//2.5 ID5

//2.10 Orange LED
//2.11 Red LED

//ADC5/Wakeup - 1.4 - wakeup
//ADC0 - 0.11 - voltage
//ADC1 - 1.0 - temp

/*********************************************************************************
**                            End Of File
*********************************************************************************/
