/*
 * task_sensor.c
 *
 */

#include "ao_tunnel_sync.h"
#include "driver.h"
#include "task_sensor.h"


#define TASK_PERIOD_MS	40


void task_sensor(void* pv_parameters)
{
	sensor_param_t* sensor_param = (sensor_param_t*)pv_parameters;

	while (1)
	{
		if (car_sensor_read(sensor_param->acces_id))
		{
			ao_tunnel_car_queue(sensor_param->tunnel_sync, sensor_param->acces_id);
		}
		vTaskDelay((TickType_t)(TASK_PERIOD_MS / portTICK_PERIOD_MS));
	}
}
