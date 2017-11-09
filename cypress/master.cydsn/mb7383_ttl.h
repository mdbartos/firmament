#ifndef MB7383_TTL_H
#define MB7383_TTL_H
    
#include "peripherals.h"
#include "device_def.h"

char *mb7383_ttl_labels[MB7383_TTL_NVARS] = {MB7383_TTL_LABEL_0};
float mb7383_ttl_readings[MB7383_TTL_NVARS] = {MB7383_TTL_DEFAULT_0};
float mb7383_ttl_invalid[MB7383_TTL_NVARS] = {MB7383_TTL_INVALID_0};
char *mb7383_ttl_str_starts[MB7383_TTL_NVARS] = {MB7383_TTL_STR_START_0};
char *mb7383_ttl_str_ends[MB7383_TTL_NVARS] = {MB7383_TTL_STR_END_0};

static DeviceConfig mb7383_ttl = 
{
    .baud = MB7383_TTL_UART_BAUD,
    .on_time = MB7383_TTL_ON_TIME,
    .mux_term = MB7383_TTL_UART_MUX_TERMINAL,
    .power_term = MB7383_TTL_POWER_TERMINAL,
    .nvars = MB7383_TTL_NVARS,
    .readings = &mb7383_ttl_readings,
    .labels = &mb7383_ttl_labels,
    .invalid = &mb7383_ttl_invalid,
    .str_starts = &mb7383_ttl_str_starts,
    .str_ends = &mb7383_ttl_str_ends
};
#endif
/* [] END OF FILE */
