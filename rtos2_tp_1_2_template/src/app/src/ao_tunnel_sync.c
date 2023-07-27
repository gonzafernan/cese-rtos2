/*
 * ao_tunnel_sync.c
 *
 */

#include <stdbool.h>

#include "ao_tunnel_sync.h"


#define AO_CAR_QUEUE_LENGTH		2


typedef struct
{
	access_t access_id;
} event_t;


void ao_tunnel_sync_task(void* pv_parameters)
{
	ao_tunnel_sync_t* hao = (ao_tunnel_sync_t*)pv_parameters;
	event_t event;

	while (1)
	{
		if (pdPASS == xQueueReceive(hao->car_queue, &event, portMAX_DELAY))
		{
			ao_access_car_release(hao->ao_access[event.access_id]);
		}

	}
}


/**
 * @brief Utility for sensor to notify car detected and queue it.
 */
bool ao_tunnel_car_queue(ao_tunnel_sync_t* hao, access_t access_id)
{
	event_t event;
	event.access_id = access_id;
	return (xQueueSend(hao->car_queue, (void*)&event, 0) == pdPASS);
}


void ao_tunnel_sync_init(ao_tunnel_sync_t* hao, ao_access_t accesses[], uint8_t access_len)
{
	for (uint8_t i = 0; i < access_len; i++)
	{
		hao->ao_access[i] = &accesses[i];
	}
	hao->car_queue = xQueueCreate(AO_CAR_QUEUE_LENGTH, sizeof(event_t));

	while (hao->car_queue == NULL)
	{
		// error handler
	}

	hao->tunnel_mutex = xSemaphoreCreateMutex();

	while (hao->tunnel_mutex == NULL)
	{
		// error handler
	}

	BaseType_t status;
	status = xTaskCreate(ao_tunnel_sync_task, "tunnel_sync_task", 128, (void*)hao, tskIDLE_PRIORITY, NULL);

	while (status != pdPASS)
	{
		// error handler
	}
}
