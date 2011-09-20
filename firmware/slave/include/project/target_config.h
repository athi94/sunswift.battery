

#define BURSTMODE_PORT 		1
#define BURSTMODE_BIT 		5
#define CAN_EN_PORT 		0
#define CAN_EN_BIT 		3
#define DISCHARGE_PORT 		0
#define DISCHARGE_BIT 		6
#define VOLT_SENSE_EN_PORT 	0
#define VOLT_SENSE_EN_BIT 	7
#define TEMP_SENSE_EN_PORT	3
#define TEMP_SENSE_EN_BIT	0
#define ID_PORT			2
#define ID0_BIT			0
#define ID1_BIT			1
#define ID2_BIT			2
#define ID3_BIT			3
#define ID4_BIT			4
#define ID5_BIT			5
#define YELLOW_LED_PORT 	2
#define YELLOW_LED_BIT 		11
#define RED_LED_PORT		2
#define RED_LED_BIT		10
#define WAKEUP_PORT		1
#define WAKEUP_BIT		4
#define VOLT_SENSE_PORT		0
#define VOLT_SENSE_BIT		11
#define TEMP_SENSE_PORT		1
#define TEMP_SENSE_BIT		0
#define INPUT			0
#define OUTPUT			1
#define ADC_VOLT		0
#define ADC_TEMP		1
#define ADC_CALB		2
#define ADC_CLKSCALE	2
#define UART_CLK		115200

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
