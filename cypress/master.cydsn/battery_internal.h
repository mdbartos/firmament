#ifndef BATTERY_INTERNAL_H
#define BATTERY_INTERNAL_H
    
#include "peripherals.h"
#include "device_def.h"

char *battery_internal_labels[BATTERY_INTERNAL_NVARS] = {BATTERY_INTERNAL_LABEL_0};
float battery_internal_readings[BATTERY_INTERNAL_NVARS] = {BATTERY_INTERNAL_DEFAULT_0};
float battery_internal_invalid[BATTERY_INTERNAL_NVARS] = {BATTERY_INTERNAL_INVALID_0};

static DeviceConfig battery_internal = 
{
    .on_time = BATTERY_INTERNAL_ON_TIME,
    .mux_term = BATTERY_INTERNAL_POWER_TERMINAL,
    .power_term = BATTERY_INTERNAL_POWER_TERMINAL,
    .nvars = BATTERY_INTERNAL_NVARS,
    .analog_convert_volts = BATTERY_INTERNAL_ANALOG_CONVERT_VOLTS,
    .analog_gain_numerator = BATTERY_INTERNAL_ANALOG_GAIN_NUMERATOR,
    .analog_gain_denominator = BATTERY_INTERNAL_ANALOG_GAIN_DENOMINATOR,
    .readings = &battery_internal_readings,
    .labels = &battery_internal_labels,
    .invalid = &battery_internal_invalid
};
#endif

/* [] END OF FILE */
