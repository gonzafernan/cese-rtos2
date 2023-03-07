/*
 * euart.c
 *
 *  Created on: Feb 15, 2023
 *      Author: seb
 */

#include <string.h>
#include "euart.h"
#include "stm32f4xx_hal.h"

#define pTX_RB          (&(phandle->tx.rb))
#define pTX_BUFFER      (phandle->tx.pbuffer)
#define pRX_RB          (&(phandle->rx.rb))
#define pRX_BUFFER      (phandle->rx.pbuffer)

void hal_receive_(euart_t *phandle)
{
  euart_hal_receive(phandle->phardware_handle, pRX_BUFFER, EUART_HAL_BUFFER_SIZE);
}

void hal_send_(euart_t *phandle)
{
  size_t tx_len = eringbuffer_read(pTX_RB, pTX_BUFFER, EUART_HAL_BUFFER_SIZE);
  euart_hal_send(phandle->phardware_handle, pTX_BUFFER, tx_len);
  phandle->tx_free = false;
}

__weak void euart_hal_receive(void* phardware_handle, uint8_t* pbuffer, size_t size)
{
  return;
}

__weak void euart_hal_send(void* phardware_handle, uint8_t* pbuffer, size_t size)
{
  return;
}

void euart_init(euart_t *phandle, void* phardware_handle, uint8_t* ptx_buffer, size_t tx_buffer_size, uint8_t* prx_buffer, size_t rx_buffer_size)
{
  phandle->phardware_handle = phardware_handle;
  eringbuffer_init(pTX_RB, ptx_buffer, tx_buffer_size);
  eringbuffer_init(pRX_RB, prx_buffer, rx_buffer_size);
  phandle->tx_free = true;

  hal_receive_(phandle);
}

size_t euart_write_buffer_len(euart_t *phandle)
{
  return eringbuffer_len(pTX_RB);
}

size_t euart_write(euart_t *phandle, const uint8_t *buffer, size_t size)
{
  size_t ret =  eringbuffer_write(pTX_RB, buffer, size);
  if(phandle->tx_free)
  {
    hal_send_(phandle);
  }
  return ret;
}

//size_t euart_write_byte(euart_t *phandle, uint8_t byte)
//{
//  return euart_write(phandle, &byte, 1);
//}

//size_t euart_swrite(euart_t *phandle, const char *str)
//{
//  return euart_write(phandle, (const uint8_t*)str, strlen(str));
//}

//size_t euart_swrite_line(euart_t *phandle, const char *str)
//{
//  size_t ret = euart_swrite(phandle, str);
//  ret += euart_swrite(phandle, "\r\n");
//  return ret;
//}

size_t euart_read_buffer_len(euart_t *phandle)
{
  return eringbuffer_len(pRX_RB);
}

size_t euart_read(euart_t *phandle, uint8_t *buffer, size_t size)
{
  return eringbuffer_read(pRX_RB, buffer, size);
}

//size_t euart_read_byte(euart_t *phandle, uint8_t* pbyte)
//{
//  return euart_read(phandle, pbyte, 1);
//}

//size_t euart_sread(euart_t *phandle, char *str, size_t max_size)
//{
//  size_t ret = euart_read(phandle, (uint8_t*)str, max_size);
//  str[ret] = '\0';
//  return ret;
//}

void euart_rx_irq(euart_t *phandle, void *phardware_handle, size_t size)
{
  if(phandle->phardware_handle != phardware_handle)
  {
    return;
  }

  if(0 < size)
  {
    eringbuffer_write(pRX_RB, pRX_BUFFER, size);
  }
  hal_receive_(phandle);
}

void euart_tx_irq(euart_t *phandle, void *phardware_handle)
{
  phandle->tx_free = true;
  if(phandle->phardware_handle != phardware_handle)
  {
    return;
  }

  if(!eringbuffer_is_empty(pTX_RB))
  {
    hal_send_(phandle);
  }
}
