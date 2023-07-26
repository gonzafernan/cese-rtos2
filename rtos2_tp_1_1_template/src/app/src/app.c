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

#include "driver.h"
#include "test.h"
#include "test_mock.h"

#include "ao_led.h"
#include "task_button.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/
ao_led_t ao_led;
button_descriptor_t btn_descriptor[BUTTON__CNT];
const char* task_button_name[BUTTON__CNT] = {"tasK_button_red", "task_button_green", "task_button_blue"};

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
		ao_led_init(&ao_led);
		ELOG("ao init");
	}

	// tasks
	{
		for (button_t i = 0; i < BUTTON__CNT; i++) {
			btn_descriptor[i].ao_led = &ao_led;
			btn_descriptor[i].button = i;

			BaseType_t status = pdPASS;
			status = xTaskCreate(task_button, task_button_name[i], 128, (void *)&btn_descriptor[i], tskIDLE_PRIORITY, NULL);
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
