/*
 * task_button.c
 *
 */

#include <stdint.h>

#include "app.h"
#include "ao_led.h"
#include "task_button.h"


#define TASK_PERIOD_MS		50

uint8_t led_command = 0x00;

void task_button(void* pv_parameters)
{
	button_descriptor_t *button_param = (button_descriptor_t*)pv_parameters;

	while(1)
	{
		ELOG("read button and send");
		if (button_read(button_param->button))
		{
			led_command |= (((uint8_t)(button_param->button)) << led_command);
		} else {
			led_command &= ~(((uint8_t)(button_param->button)) << led_command);
		}
		ao_led_command_send(button_param->ao_led, led_command);
		vTaskDelay((TickType_t)(TASK_PERIOD_MS / portTICK_PERIOD_MS));
	}
}
