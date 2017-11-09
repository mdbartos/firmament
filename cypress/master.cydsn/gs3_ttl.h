#ifndef GS3_TTL_H
#define GS3_TTL_H
    
#include "peripherals.h"
#include "device_def.h"

char *gs3_ttl_labels[GS3_TTL_NVARS] = {GS3_TTL_LABEL_0, GS3_TTL_LABEL_1, GS3_TTL_LABEL_2, GS3_TTL_LABEL_3};
float gs3_ttl_readings[GS3_TTL_NVARS] = {GS3_TTL_DEFAULT_0, GS3_TTL_DEFAULT_1, GS3_TTL_DEFAULT_2, GS3_TTL_DEFAULT_3};
float gs3_ttl_invalid[GS3_TTL_NVARS] = {GS3_TTL_INVALID_0, GS3_TTL_INVALID_1, GS3_TTL_INVALID_2, GS3_TTL_INVALID_3};
char *gs3_ttl_str_starts[GS3_TTL_NVARS] = {GS3_TTL_STR_START_0, GS3_TTL_STR_START_1, GS3_TTL_STR_START_2, GS3_TTL_STR_START_3};
char *gs3_ttl_str_ends[GS3_TTL_NVARS] = {GS3_TTL_STR_END_0, GS3_TTL_STR_END_1, GS3_TTL_STR_END_2, GS3_TTL_STR_END_3};

static DeviceConfig gs3_ttl = 
{
    .baud = GS3_TTL_UART_BAUD,
    .on_time = GS3_TTL_ON_TIME,
    .mux_term = GS3_TTL_UART_MUX_TERMINAL,
    .power_term = GS3_TTL_POWER_TERMINAL,
    .nvars = GS3_TTL_NVARS,
    .readings = &gs3_ttl_readings,
    .labels = &gs3_ttl_labels,
    .invalid = &gs3_ttl_invalid,
    .str_starts = &gs3_ttl_str_starts,
    .str_ends = &gs3_ttl_str_ends
};
#endif
/* [] END OF FILE */
