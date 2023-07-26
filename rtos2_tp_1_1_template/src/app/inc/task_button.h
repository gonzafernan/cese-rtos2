/*
 * task_button.h
 *
 *  Created on: Jul 26, 2023
 *      Author: ggf
 */

#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_


typedef struct
{
	button_t button;
	ao_led_t* ao_led;

} button_descriptor_t;


void task_button(void* pv_parameters);


#endif /* TASK_BUTTON_H_ */
