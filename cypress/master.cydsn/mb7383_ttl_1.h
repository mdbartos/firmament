#ifndef MB7383_TTL_1_H
#define MB7383_TTL_1_H
    
#include "peripherals.h"
#include "device_dict.h"

char *mb7383_ttl_1_labels[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_LABEL_0};
float mb7383_ttl_1_readings[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_DEFAULT_0};
float mb7383_ttl_1_invalid[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_INVALID_0};
char *mb7383_ttl_1_str_starts[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_STR_START_0};
char *mb7383_ttl_1_str_ends[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_STR_END_0};

static DeviceDict mb7383_ttl_1 = 
{
    .baud = MB7383_TTL_1_UART_BAUD,
    .on_time = MB7383_TTL_1_ON_TIME,
    .mux_term = MB7383_TTL_1_UART_MUX_TERMINAL,
    .power_term = MB7383_TTL_1_POWER_TERMINAL,
    .nvars = MB7383_TTL_1_NVARS,
    .readings = &mb7383_ttl_1_readings,
    .labels = &mb7383_ttl_1_labels,
    .invalid = &mb7383_ttl_1_invalid,
    .str_starts = &mb7383_ttl_1_str_starts,
    .str_ends = &mb7383_ttl_1_str_ends
};
#endif
/* [] END OF FILE */
