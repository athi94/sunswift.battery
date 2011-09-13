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

#include <arch/timer32.h>
#include <arch/gpio.h>
#include <arch/uart.h>
#include <arch/type.h>
#include <arch/can.h>
#include <arch/i2c.h>
#include <arch/adc.h>

#include <math.h>

void in_channel_0_handler(int32_t value, uint32_t src_time) {
	UART_printf("in_channel_0_handler got called with value %d time at source %d\n\r", value, src_time);
}


//int ADCValue[8] = {0};

#define DEBUG TRUE

int main (void) {
	int on=0, ID, calb;
	
	int batt_voltage = 0;    
	
	//init();
	//ID = readID();
	//calb = readCalibration();
	//	GPIOhandle_scandalSetValue(RED_LED_PORT, RED_LED_PIN,1);

	int i = 0; /* Used in main loop */
	uint32_t value = 0xaa;
	setup_ports();
	
	scandal_init();
// 	enable_timer32(0);
	UARTInit(115200);
	//ADCInit(4);
	sc_time_t one_sec_timer = sc_get_timer(); /* Initialise the timer variable */
	sc_time_t test_in_timer = sc_get_timer(); /* Initialise the timer variable */
	
	/* Set LEDs to known states, i.e. on */
	red_led(1);
	orange_led(0);
	
	scandal_delay(100); /* wait for the UART clocks to settle */
	
	/* Display welcome header over UART */
	UART_printf("Welcome to the template project! This is coming out over UART1\n\r");
	UART_printf("The 2 debug LEDs should blink at a rate of 1HZ\n\r");
	UART_printf("If you configure the in channel 0, I should print a message upon receipt of such a channel message\n\r");
	
	GPIOSetValue(CAN_EN_PORT, CAN_EN_PIN, 1);
	
	scandal_register_in_channel_handler(0, &in_channel_0_handler);
	
	/* This is the main loop, go for ever! */
	while (1) {
		/* This checks whether there are pending requests from CAN, and sends a heartbeat message.
		* The heartbeat message encodes some data in the first 4 bytes of the CAN message, such as
		* the number of errors and the version of scandal */
		//handle_scandal();
		
		GPIOSetValue(DISCHARGE_PORT, DISCHARGE_PIN, ON);
		GPIOSetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_PIN, ON);
		
		scandal_delay(1000);
		GPIOSetValue(DISCHARGE_PORT, DISCHARGE_PIN, OFF);
		GPIOSetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_PIN, OFF);
		scandal_delay(1000);
		/* Send a UART message and flash an LED every second */
		if(sc_get_timer() >= one_sec_timer + 1000) {
			toggle_red_led();
			toggle_orange_led();
			one_sec_timer = sc_get_timer();
			//batt_voltage = readVoltage();
			/*scandal_send_channel(TELEM_LOW, // priority 
							0,      // channel num 
							batt_voltage    // value 
							);*/
		}
// 			/* Send the message */
// 			UART_printf("This is the 1 second timer... %d\n\r", i++);
// 			
// 			/* Send a channel message with a blerg value at low priority on channel 0 */
// 			
// 					     
// 			/* Twiddle the LEDs */
// 			toggle_orange_led();
// 			toggle_red_led();
// 			
// 			/* Update the timer */
// 			one_sec_timer = sc_get_timer();
// 		}
// 		
// 		if(scandal_get_in_channel_rcvd_time(TEMPLATE_TEST_IN) > test_in_timer) {
// 			
// 			value = scandal_get_in_channel_value(TEMPLATE_TEST_IN);
// 			
// 			UART_printf("I received a channel message in the main loop on in_channel 0, value %d at time %d\n\r", 
// 				    value, scandal_get_in_channel_rcvd_time(TEMPLATE_TEST_IN));
// 				    
// 				    if(scandal_get_in_channel_value(TEMPLATE_TEST_IN) == 1) {
// 					    toggle_red_led();
// 				    } else {
// 					    toggle_orange_led();
// 				    }
// 				    
// 				    test_in_timer = scandal_get_in_channel_rcvd_time(TEMPLATE_TEST_IN);
// 		}
// 		
 	}

}


int readVoltage(void) {
	GPIOSetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_PIN, ON);
	scandal_delay(100);
	ADCRead(ADC_VOLT);
	GPIOSetValue(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_PIN, OFF);
	
	return ADCValue[ADC_VOLT];	//error checking?
}

int readTemperature(void) {
	
	//enable voltage sense mosfet
	GPIOSetValue(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_PIN, ON);
	//wait?
	scandal_delay(100);
	//read voltage
	ADCRead(ADC_TEMP);
	//disable voltage sense mosfet
	GPIOSetValue(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_PIN, OFF);
	
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
	GPIOSetValue(DISCHARGE_PORT, DISCHARGE_PIN, ON);
	//delay for time, or perhaps should specify a voltage to discharge to?
	GPIOSetValue(DISCHARGE_PORT, DISCHARGE_PIN, OFF);
	
}

//determine ID based on 6 GPIO pins
int readID(void) {
	int ID = 0;
	ID |= (GPIO_GetValue(ID_PORT, ID0_PIN));
	ID |= (GPIO_GetValue(ID_PORT, ID1_PIN)<<1);
	ID |= (GPIO_GetValue(ID_PORT, ID2_PIN)<<2);
	ID |= (GPIO_GetValue(ID_PORT, ID3_PIN)<<3);
	ID |= (GPIO_GetValue(ID_PORT, ID4_PIN)<<4);
	ID |= (GPIO_GetValue(ID_PORT, ID5_PIN)<<5);
	return ID;
}

void burstmode(int mode) {
	GPIOSetValue(BURSTMODE_PORT, BURSTMODE_PIN, mode);
}

void setup_ports(void) {
	/* Initialize GPIO (sets up clock) */
	GPIOInit();
	
	GPIOSetDir(ID_PORT, ID0_PIN, INPUT);
	GPIOSetDir(ID_PORT, ID1_PIN, INPUT);
	GPIOSetDir(ID_PORT, ID2_PIN, INPUT);
	GPIOSetDir(ID_PORT, ID3_PIN, INPUT);
	GPIOSetDir(ID_PORT, ID4_PIN, INPUT);
	GPIOSetDir(ID_PORT, ID5_PIN, INPUT);
	
	GPIOSetDir(BURSTMODE_PORT, BURSTMODE_PIN, OUTPUT);
	GPIOSetDir(CAN_EN_PORT, CAN_EN_PIN, OUTPUT);
	GPIOSetDir(DISCHARGE_PORT, DISCHARGE_PIN, OUTPUT);
	GPIOSetValue(DISCHARGE_PORT, DISCHARGE_PIN, OFF);
	GPIOSetDir(VOLT_SENSE_EN_PORT, VOLT_SENSE_EN_PIN, OUTPUT);
	GPIOSetDir(TEMP_SENSE_EN_PORT, TEMP_SENSE_EN_PIN, OUTPUT);
	GPIOSetDir(ORANGE_LED_PORT, ORANGE_LED_PIN, OUTPUT);
	GPIOSetDir(RED_LED_PORT, RED_LED_PIN, OUTPUT);
	GPIOSetDir(WAKEUP_PORT, WAKEUP_PIN, INPUT);

	//delay for time, or perhaps should specify a voltage to discharge to?
}

// int main(void)
// {
	
	
// 		/* Each time we wake up... */
// 	/* Check TimeTick to see whether to set or clear the LED I/O pin */
// 	if ( (timer32_0_counter%(LED_TOGGLE_TADCValue[ADCChannels);ICKS/COUNT_MAX)) < ((LED_TOGGLE_TICKS/COUNT_MAX)/2) ) {
// 		GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
// 		on=0;
// 	} else {
// 		GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
// 		on=1;		
// 	}
// 	ADCRead(0);
// 	if(ADCValue[0] == 0) {
// 		GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
// 		UARTSend("lol", 3);
// 	} else if(ADCValue[0] < 512) {
// 		GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
// 		on=1;	
// 		UARTSend("b", 1);
// 	} else {
// 		GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
// 		on=0;
// 	}
