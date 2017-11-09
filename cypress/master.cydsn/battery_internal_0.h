#ifndef BATTERY_INTERNAL_0_H
#define BATTERY_INTERNAL_0_H
    
#include "peripherals.h"
#include "device_dict.h"

char *battery_internal_0_labels[BATTERY_INTERNAL_0_NVARS] = {BATTERY_INTERNAL_0_LABEL_0};
float battery_internal_0_readings[BATTERY_INTERNAL_0_NVARS] = {BATTERY_INTERNAL_0_DEFAULT_0};
float battery_internal_0_invalid[BATTERY_INTERNAL_0_NVARS] = {BATTERY_INTERNAL_0_INVALID_0};

static DeviceDict battery_internal_0 = 
{
    .on_time = BATTERY_INTERNAL_0_ON_TIME,
    .mux_term = BATTERY_INTERNAL_0_POWER_TERMINAL,
    .power_term = BATTERY_INTERNAL_0_POWER_TERMINAL,
    .nvars = BATTERY_INTERNAL_0_NVARS,
    .analog_convert_volts = BATTERY_INTERNAL_0_ANALOG_CONVERT_VOLTS,
    .analog_gain_numerator = BATTERY_INTERNAL_0_ANALOG_GAIN_NUMERATOR,
    .analog_gain_denominator = BATTERY_INTERNAL_0_ANALOG_GAIN_DENOMINATOR,
    .readings = &battery_internal_0_readings,
    .labels = &battery_internal_0_labels,
    .invalid = &battery_internal_0_invalid
};
#endif

/* [] END OF FILE */
