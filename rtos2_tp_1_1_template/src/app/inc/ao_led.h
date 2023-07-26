/*
 * ao_led.h
 *
 */

#ifndef AO_LED_H_
#define AO_LED_H_

#include "driver.h"

typedef struct ao_led_s ao_led_t;

struct ao_led_s
{
	QueueHandle_t hqueue;
};

bool ao_led_command_send(ao_led_t* hao, uint8_t command);
void ao_led_init(ao_led_t* hao);

#endif /* AO_LED_H_ */
