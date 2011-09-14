/****************************************************************************
 *   $Id:: i2c_main.c 4785 2010-09-03 22:39:27Z nxp21346                    $
 *   Project: NXP LPC11xx I2C example
 *
 *   Description:
 *     This file contains I2C test modules, main entry, to test I2C APIs.
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

#include <scandal/engine.h> /* for general scandal functions */
#include <scandal/message.h> /* for TELEM_LOW */

#include <project/driver_config.h>
#include <project/target_config.h>

#include <arch/timer16.h>
#include <arch/gpio.h>
#include <arch/uart.h>
#include <arch/types.h>
#include <arch/can.h>
#include <arch/i2c.h>
#include <arch/adc.h>

#include <math.h>

void in_channel_0_handler(int32_t value, uint32_t src_time) {
	UART_printf("in_channel_0_handler got called with value %d time at source %d\n\r", value, src_time);
}


//int ADCValue[8] = {0};

#define DEBUG TRUE


int readVoltage(void);
int readCalibration(void);
int readID(void);
void burstmode(int mode);
void setup_ports(void);
int discharge(int argument, int mode);
int readTemperature(void);


int main (void) {
	int on=0, ID, calb;
	
	int batt_voltage = 0;    
	
	//init();
	//ID = readID();
	//calb = readCalibration();
	//	GPIO_SetValue(RED_LED_PORT, RED_LED_BIT,1);

	int i = 0; /* Used in main loop */
	uint32_t value = 0xaa;
	setup_ports();
	
	scandal_init();
	UART_Init(115200);
	ADCInit(ADC_CLK);
	sc_time_t one_sec_timer = sc_get_timer(); /* Initialise the timer variable */
	sc_time_t test_in_timer = sc_get_timer(); /* Initialise the timer variable */

	ADCValue[0] = 1;
	
	/* Set LEDs to known states, i.e. on */
	red_led(1);
	yellow_led(0);
	
	scandal_delay(100); /* wait for the UART clocks to settle */
	
	
	GPIO_SetValue(CAN_EN_PORT, CAN_EN_BIT, 1);
	
	scandal_register_in_channel_handler(0, &in_channel_0_handler);
	
	/* This is the main loop, go for ever! */
	while (1) {
		/* This checks whether there are pending requests from CAN, and sends a heartbeat message.
		* The heartbeat message encodes some data in the first 4 bytes of the CAN message, such as
		* the number of errors and the version of scandal */
		//handle_scandal();
		
		//GPIO_SetValue(DISCHARGE_PORT, DISCHARGE_BIT, ON);
		//GPIO_SetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_BIT, ON);
		
		//scandal_delay(1000);
		//GPIO_SetValue(DISCHARGE_PORT, DISCHARGE_BIT, OFF);
		//GPIO_SetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_BIT, OFF);
		//scandal_delay(1000);
		/* Send a UART message and flash an LED every second */
		if(sc_get_timer() >= one_sec_timer + 1000) {
			toggle_red_led();
			toggle_yellow_led();
			one_sec_timer = sc_get_timer();
			batt_voltage = readVoltage();
			scandal_send_channel(TELEM_LOW, // priority 
							0,      // channel num 
							batt_voltage    // value 
							);
		}
	}
}


int readVoltage(void) {
	//int voltage = 0;
	GPIO_SetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_BIT, ON);
	scandal_delay(500);
	ADCRead(ADC_VOLT);
	GPIO_SetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_BIT, OFF);
	
	return ADCValue[ADC_VOLT];	//error checking?
}

int readTemperature(void) {
	
	GPIO_SetValue(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_BIT, ON);
	scandal_delay(100);
	ADCRead(ADC_TEMP);
	GPIO_SetValue(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_BIT, OFF);
	
	return ADCValue[ADC_TEMP];	//error checking?
}

int readCalibration(void) {
	ADCRead(ADC_CALB);
	return ADCValue[ADC_CALB];
}

//discharge mode = time || voltage, argument = time (s) || voltage (Volts)
int discharge(int argument, int mode) { 
	//start discharger
	//set timer interrupt
	//stop discharge
	GPIO_SetValue(DISCHARGE_PORT, DISCHARGE_BIT, ON);
	//delay for time, or perhaps should specify a voltage to discharge to?
	GPIO_SetValue(DISCHARGE_PORT, DISCHARGE_BIT, OFF);
	return 0;
}

//determine ID based on 6 GPIO_ pins
int readID(void) {
	int ID = 0;
	ID |= (GPIO_GetValue(ID_PORT, ID0_BIT));
	ID |= (GPIO_GetValue(ID_PORT, ID1_BIT)<<1);
	ID |= (GPIO_GetValue(ID_PORT, ID2_BIT)<<2);
	ID |= (GPIO_GetValue(ID_PORT, ID3_BIT)<<3);
	ID |= (GPIO_GetValue(ID_PORT, ID4_BIT)<<4);
	ID |= (GPIO_GetValue(ID_PORT, ID5_BIT)<<5);
	return ID;
}

void burstmode(int mode) {
	GPIO_SetValue(BURSTMODE_PORT, BURSTMODE_BIT, mode);
}

void setup_ports(void) {
	/* Initialize GPIO_ (sets up clock) */
	GPIO_Init();
	
	GPIO_SetDir(ID_PORT, ID0_BIT, INPUT);
	GPIO_SetDir(ID_PORT, ID1_BIT, INPUT);
	GPIO_SetDir(ID_PORT, ID2_BIT, INPUT);
	GPIO_SetDir(ID_PORT, ID3_BIT, INPUT);
	GPIO_SetDir(ID_PORT, ID4_BIT, INPUT);
	GPIO_SetDir(ID_PORT, ID5_BIT, INPUT);
	
	GPIO_SetDir(BURSTMODE_PORT, BURSTMODE_BIT, OUTPUT);
	GPIO_SetDir(CAN_EN_PORT, CAN_EN_BIT, OUTPUT);
	GPIO_SetDir(DISCHARGE_PORT, DISCHARGE_BIT, OUTPUT);
	GPIO_SetValue(DISCHARGE_PORT, DISCHARGE_BIT, OFF);
	GPIO_SetDir(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_BIT, OUTPUT);
	GPIO_SetDir(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_BIT, OUTPUT);
	GPIO_SetDir(YELLOW_LED_PORT, YELLOW_LED_BIT, OUTPUT);
	GPIO_SetDir(RED_LED_PORT, RED_LED_BIT, OUTPUT);
	GPIO_SetDir(WAKEUP_PORT, WAKEUP_BIT, INPUT);

	//delay for time, or perhaps should specify a voltage to discharge to?
}

// int main(void)
// {
	
	
// 		/* Each time we wake up... */
// 	/* Check TimeTick to see whether to set or clear the LED I/O pin */
// 	if ( (timer32_0_counter%(LED_TOGGLE_TADCValue[ADCChannels);ICKS/COUNT_MAX)) < ((LED_TOGGLE_TICKS/COUNT_MAX)/2) ) {
// 		GPIO_SetValue( LED_PORT, LED_BIT, LED_OFF );
// 		on=0;
// 	} else {
// 		GPIO_SetValue( LED_PORT, LED_BIT, LED_ON );
// 		on=1;		
// 	}
// 	ADCRead(0);
// 	if(ADCValue[0] == 0) {
// 		GPIO_SetValue( LED_PORT, LED_BIT, LED_ON );
// 		UARTSend("lol", 3);
// 	} else if(ADCValue[0] < 512) {
// 		GPIO_SetValue( LED_PORT, LED_BIT, LED_ON );
// 		on=1;	
// 		UARTSend("b", 1);
// 	} else {
// 		GPIO_SetValue( LED_PORT, LED_BIT, LED_OFF );
// 		on=0;
// 	}
