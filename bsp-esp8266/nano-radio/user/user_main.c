/*
 *  NanoRadio (Open source IoT hardware)
 *
 *  This project is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License(GPL)
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This project is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */
#include "portable.h"
#include "util-logtrace.h"
#include "xapi.h"
#include "tasks.h"

void ICACHE_FLASH_ATTR
user_init(void)
{
#if defined(DELTA_SIGMA_HACK)
	SET_PERI_REG_MASK(0x3ff00014, BIT(0));
	os_update_cpu_frequency(160);
#endif
	
	//Set the UART to 74880 baud
	UART_SetBaudrate(0, 74880);

	printf("\n\nHardware initialized. Waiting for network.\n");
  
  ws_log_init();
  
  task_audio_init();
  //task_audio_open("47.110.185.4", "/386.mp3", 80);
}
