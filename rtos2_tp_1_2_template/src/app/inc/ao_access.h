/*
 * ao_access.h
 *
 *  Created on: Jul 27, 2023
 *      Author: ggf
 */

#ifndef AO_ACCESS_H_
#define AO_ACCESS_H_


#include "app.h"
#include "driver.h"


typedef struct
{
	access_t access_id;
	SemaphoreHandle_t hsemaph;
} ao_access_t;


void ao_access_init(ao_access_t* hao, access_t access_id);
bool ao_access_car_detect(ao_access_t* hao);


#endif /* AO_ACCESS_H_ */
