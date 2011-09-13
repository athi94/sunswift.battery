/* --------------------------------------------------------------------------
	Scandal Engine
	File name: led.c
	Author: Etienne Le Sueur
 
    Copyright (C) 2011 Etienne Le Sueur.

	Date: 29/08/2011
   -------------------------------------------------------------------------- */ 

/* 
 * This file is part of Scandal.
 * 
 * Scandal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * Scandal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with Scandal.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <scandal/types.h>

#include <project/driver_config.h>
#include <project/target_config.h>

#include <arch/gpio.h>

/* this is using two different levels of abstraction to twiddle the LEDs. We can
 * probably go even further up down thr rabbit hole to just modifying registers
 */

void red_led(u08 on) {
	if (on)
		GPIOSetValue(RED_LED_PORT,RED_LED_PIN,0);
	else
		GPIOSetValue(RED_LED_PORT,RED_LED_PIN,1);
}

void toggle_red_led(void) {
	LPC_GPIO[RED_LED_PORT]->MASKED_ACCESS[(1<<RED_LED_PIN)] ^= (1<<RED_LED_PIN);
}

void orange_led(u08 on) {
	if (on)
		GPIOSetValue(ORANGE_LED_PORT,ORANGE_LED_PIN,0);
	else
		GPIOSetValue(ORANGE_LED_PORT,ORANGE_LED_PIN,1);
}

void toggle_orange_led(void) {
	LPC_GPIO[ORANGE_LED_PORT]->MASKED_ACCESS[(1<<ORANGE_LED_PIN)] ^= (1<<ORANGE_LED_PIN);
}

