/*
 * task_sensor.c
 *
 */

#include "ao_access.h"
#include "driver.h"
#include "task_sensor.h"

#define TASK_PERIOD_MS	40

void task_sensor(void* pv_parameters)
{
	ao_access_t* ao_access = (ao_access_t*)pv_parameters;

	while (1)
	{
		if (car_sensor_read(ao_access->access_id))
		{
			ao_access_car_detect(ao_access);
		}
		vTaskDelay((TickType_t)(TASK_PERIOD_MS / portTICK_PERIOD_MS));
	}
}
