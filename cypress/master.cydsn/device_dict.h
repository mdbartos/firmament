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
    uint8 i2c_slave_address;
    int i2c_delay;
    uint8 i2c_command_buffer_size;
    uint8 (*i2c_read_command)[];
    uint8 i2c_affirm_response_code;
    float (*readings)[];
    float (*invalid)[];
    char *(*labels)[];
    char *(*str_starts)[];
    char *(*str_ends)[];
} DeviceDict; 

#endif
/* [] END OF FILE */
