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
 
#include "af-interface.h"

static adif_format_t adif_format;
#if defined(USING_ADIF_RT)
extern adif_t adif_rt;
#endif
#if defined(USING_ADIF_ESP_I2S)
extern adif_t adif_esp_i2s;
#endif
#if defined(USING_ADIF_ESP_I2S_DSM)
extern adif_t adif_esp_i2s_dsm;
#endif

static const adif_t *adifs[] =
  {
#if defined(USING_ADIF_RT)
    &adif_rt,
#endif
#if defined(USING_ADIF_ESP_I2S)
    &adif_esp_i2s,
#endif
#if defined(USING_ADIF_ESP_I2S_DSM)
    &adif_esp_i2s_dsm,
#endif
    NULL
  };

const adif_t *
NC_P(adif_init)(int adif_index)
{
  int i;
  const adif_t *adif;
  for(i = 0, adif = adifs[0]; adifs[i]; i++)
    {
      if(adif->adif_index == adif_index)
        break;
    }
  
  if( !adif ) return NULL;
  if( !adif->init(0) ) return adif;
  return NULL;
}

void
NC_P(adif_uninit)(const adif_t *adif)
{
  adif->uninit(0);
}

int
NC_P(adif_config)(const adif_t *adif, const adif_format_t *format)
{
  if( adif_format.sample_rate != format->sample_rate ||
      adif_format.bit_depth != format->bit_depth ||
      adif_format.channels != format->channels )
    {
      adif_format = *format;
      return adif->config(format, 0);
    }
  return 0;
}

unsigned
NC_P(adif_write)(const adif_t *adif, const void *buff, unsigned size)
{
  return adif->write(buff, size, 0);
}
