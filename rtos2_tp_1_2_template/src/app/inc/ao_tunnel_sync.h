/*
 * ao_tunnel_sync.h
 *
 */

#ifndef AO_TUNNEL_SYNC_H_
#define AO_TUNNEL_SYNC_H_

#include "app.h"
#include "ao_access.h"
#include "driver.h"


typedef struct
{
	QueueHandle_t car_queue;			// Access priority handler
	SemaphoreHandle_t tunnel_mutex;		// Tunnel resource protection
	ao_access_t* ao_access[ACCESS__CNT];	// Accesses AO reference

} ao_tunnel_sync_t;


void ao_tunnel_sync_init(ao_tunnel_sync_t* hao, ao_access_t accesses[], uint8_t access_len);
bool ao_tunnel_car_queue(ao_tunnel_sync_t* hao, access_t access_id);


#endif /* AO_TUNNEL_SYNC_H_ */
