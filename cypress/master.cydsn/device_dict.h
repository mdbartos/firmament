#ifndef DEVICE_DICT_H
#define DEVICE_DICT_H
    
#include <project.h>

typedef struct {
    uint32_t baud;
    int on_time;
    uint8 mux_term;
    uint8 power_term;
    uint8 nvars;
    uint8 analog_convert_volts;
    float analog_gain_numerator;
    float analog_gain_denominator;
    float (*readings)[];
    float (*invalid)[];
    char *(*labels)[];
    char *(*str_starts)[];
    char *(*str_ends)[];
} DeviceDict; 

#endif
/* [] END OF FILE */
