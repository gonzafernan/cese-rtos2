/*
 * ao_access.c
 *
 */

#include "ao_access.h"
#include "ao_tunnel_sync.h"
#include "driver.h"


#define ACCESS_OPEN_TIME_MS		800
#define TUNNEL_TRAVEL_TIME_MS	1800


static void ao_access_task(void* pv_parameters)
{
	ao_access_t* hao = (ao_access_t*)pv_parameters;

	while (1)
	{
		if (pdPASS == xSemaphoreTake(hao->hsemaph, portMAX_DELAY))
		{
			// Take tunnel resource
			if (pdPASS == xSemaphoreTake(hao->tunnel_mutex, portMAX_DELAY))
			{
				access_open(hao->access_id);
				vTaskDelay((TickType_t)(ACCESS_OPEN_TIME_MS / portTICK_PERIOD_MS));
				access_close(hao->access_id);
			}
			// Car travel through tunnel (> 2sec)
			vTaskDelay((TickType_t)(TUNNEL_TRAVEL_TIME_MS / portTICK_PERIOD_MS));
			xSemaphoreGive(hao->tunnel_mutex);
		}

	}
}


bool ao_access_car_release(ao_access_t* hao)
{
	return (xSemaphoreGive(hao->hsemaph) == pdPASS);
}


void ao_access_init(ao_access_t* hao, access_t access_id, SemaphoreHandle_t tunnel_mutex)
{
	hao->access_id = access_id;
	hao->tunnel_mutex = tunnel_mutex;
	hao->hsemaph = xSemaphoreCreateBinary();

	while (hao->hsemaph == NULL)
	{
		// error handler
	}

	BaseType_t status;
	status = xTaskCreate(ao_access_task, "task_ao_access", 128, (void*)hao, tskIDLE_PRIORITY, NULL);

	while (status != pdPASS)
	{
		// error handler
	}
}
