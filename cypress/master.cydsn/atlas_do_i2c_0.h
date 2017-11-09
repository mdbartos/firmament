#ifndef ATLAS_DO_I2C_0_H
#define ATLAS_DO_I2C_0_H
    
#include "peripherals.h"
#include "device_dict.h"

char *atlas_do_i2c_0_labels[ATLAS_DO_I2C_0_NVARS] = {ATLAS_DO_I2C_0_LABEL_0};
float atlas_do_i2c_0_readings[ATLAS_DO_I2C_0_NVARS] = {ATLAS_DO_I2C_0_DEFAULT_0};
float atlas_do_i2c_0_invalid[ATLAS_DO_I2C_0_NVARS] = {ATLAS_DO_I2C_0_INVALID_0};
char *atlas_do_i2c_0_str_starts[ATLAS_DO_I2C_0_NVARS] = {ATLAS_DO_I2C_0_STR_START_0};
char *atlas_do_i2c_0_str_ends[ATLAS_DO_I2C_0_NVARS] = {ATLAS_DO_I2C_0_STR_END_0};

uint8 atlas_do_i2c_0_read_command[ATLAS_DO_I2C_0_COMMAND_BUFFER_SIZE] = ATLAS_DO_I2C_0_READ_COMMAND;

static DeviceDict atlas_do_i2c_0 = 
{
    .on_time = ATLAS_DO_I2C_0_ON_TIME,
    .power_term = ATLAS_DO_I2C_0_POWER_TERMINAL,
    .nvars = ATLAS_DO_I2C_0_NVARS,
    .i2c_slave_address = ATLAS_DO_I2C_0_SLAVE_ADDRESS,
    .i2c_delay = ATLAS_DO_I2C_0_DELAY,
    .i2c_command_buffer_size = ATLAS_DO_I2C_0_COMMAND_BUFFER_SIZE,
    .i2c_read_command = &atlas_do_i2c_0_read_command,
    .i2c_affirm_response_code = ATLAS_DO_I2C_0_AFFIRM_RESPONSE_CODE,
    .readings = &atlas_do_i2c_0_readings,
    .labels = &atlas_do_i2c_0_labels,
    .invalid = &atlas_do_i2c_0_invalid,
    .str_starts = &atlas_do_i2c_0_str_starts,
    .str_ends = &atlas_do_i2c_0_str_ends
};
#endif

/* [] END OF FILE */
