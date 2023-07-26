/*
 * ao_led.c
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "app.h"
#include "ao_led.h"
#include "driver.h"


#define AO_LED_QUEUE_LENGTH		5


typedef struct
{
	uint8_t command;
} event_t;


static void ao_led_task(void* pv_parameters)
{
	ao_led_t* hao = (ao_led_t*)pv_parameters;
	event_t event;

	while (1)
	{
		if (pdPASS == xQueueReceive(hao->hqueue, &event, portMAX_DELAY))
		{
			ELOG("ao_led command:%d", event.command);
			led_command_send(event.command);
		}
	}
}


bool ao_led_command_send(ao_led_t* hao, uint8_t command)
{
	event_t event;
	event.command = command;
	return (xQueueSend(hao->hqueue, (void*)&event, 0) == pdPASS);
}


void ao_led_init(ao_led_t* hao)
{
	hao->hqueue = xQueueCreate(AO_LED_QUEUE_LENGTH, sizeof(event_t));

	while (hao->hqueue == NULL)
	{
		// error handler
	}

	BaseType_t status;
	status = xTaskCreate(ao_led_task, "task_ao_led", 128, (void*)hao, tskIDLE_PRIORITY, NULL);

	while (status == pdPASS)
	{
		// error handler
	}
}
