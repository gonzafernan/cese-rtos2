/*
 * Copyright (c) 2023 Sebastian Bedin <sebabedin@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : app.c
 * @date   : Feb 17, 2023
 * @author : Sebastian Bedin <sebabedin@gmail.com>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ao_access.h"
#include "driver.h"
#include "task_sensor.h"
#include "test.h"
#include "test_mock.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/
const char* task_sensor_name[ACCESS__CNT] = {"task_sensor_east", "task_sensor_west"};

ao_access_t ao_access_arr[ACCESS__CNT];

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/

/********************** external functions definition ************************/

void app_init(void)
{
	// drivers
	{
		driver_init();
		ELOG("drivers init");
	}

	// test
	{
		test_init();
		ELOG("test init");
	}

	// OA
	{
		ao_tunnel_init();
		for (access_t i = 0; i < ACCESS__CNT; i++)
		{
			ao_access_init(&ao_access_arr[i], i);
		}
		ELOG("ao init");
	}

	// tasks
	{
		BaseType_t status;

		for (access_t i = 0; i < ACCESS__CNT; i++)
		{
			status = xTaskCreate(task_sensor, task_sensor_name[i], 128, (void*)&ao_access_arr[i], tskIDLE_PRIORITY, NULL);
			while (pdPASS != status)
			{
				// error
			}
		}
		ELOG("tasks init");
	}

	ELOG("app init");
}

/********************** end of file ******************************************/
