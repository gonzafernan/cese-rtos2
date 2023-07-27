/*
 * task_sensor.h
 *
 */

#ifndef TASK_SENSOR_H_
#define TASK_SENSOR_H_


#include "test_mock.h"


typedef struct
{
	ao_tunnel_sync_t* tunnel_sync;	// Tunnel sync thread
	access_t acces_id;				// Access associated to sensor

} sensor_param_t;

void task_sensor(void* pv_parameters);


#endif /* TASK_SENSOR_H_ */
