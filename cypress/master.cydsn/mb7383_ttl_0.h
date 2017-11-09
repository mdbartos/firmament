#ifndef MB7383_TTL_0_H
#define MB7383_TTL_0_H
    
#include "peripherals.h"
#include "device_dict.h"

char *mb7383_ttl_0_labels[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_LABEL_0};
float mb7383_ttl_0_readings[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_DEFAULT_0};
float mb7383_ttl_0_invalid[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_INVALID_0};
char *mb7383_ttl_0_str_starts[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_STR_START_0};
char *mb7383_ttl_0_str_ends[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_STR_END_0};

static DeviceDict mb7383_ttl_0 = 
{
    .baud = MB7383_TTL_0_UART_BAUD,
    .on_time = MB7383_TTL_0_ON_TIME,
    .mux_term = MB7383_TTL_0_UART_MUX_TERMINAL,
    .power_term = MB7383_TTL_0_POWER_TERMINAL,
    .nvars = MB7383_TTL_0_NVARS,
    .readings = &mb7383_ttl_0_readings,
    .labels = &mb7383_ttl_0_labels,
    .invalid = &mb7383_ttl_0_invalid,
    .str_starts = &mb7383_ttl_0_str_starts,
    .str_ends = &mb7383_ttl_0_str_ends
};
#endif
/* [] END OF FILE */
