#ifndef PERIPHERAL_INSTANCES_H
#define PERIPHERAL_INSTANCES_H

#include "peripheral_globals.h"
#include "device_dict.h"

// Atlas DO I2C
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

// Battery internal
char *battery_internal_0_labels[BATTERY_INTERNAL_ANALOG_DELSIG_0_NVARS] = {BATTERY_INTERNAL_ANALOG_DELSIG_0_LABEL_0};
float battery_internal_0_readings[BATTERY_INTERNAL_ANALOG_DELSIG_0_NVARS] = {BATTERY_INTERNAL_ANALOG_DELSIG_0_DEFAULT_0};
float battery_internal_0_invalid[BATTERY_INTERNAL_ANALOG_DELSIG_0_NVARS] = {BATTERY_INTERNAL_ANALOG_DELSIG_0_INVALID_0};
static DeviceDict battery_internal_0 = 
{
    .on_time = BATTERY_INTERNAL_ANALOG_DELSIG_0_ON_TIME,
    .mux_term = BATTERY_INTERNAL_ANALOG_DELSIG_0_POWER,
    .power_term = BATTERY_INTERNAL_ANALOG_DELSIG_0_POWER,
    .nvars = BATTERY_INTERNAL_ANALOG_DELSIG_0_NVARS,
    .analog_convert_volts = BATTERY_INTERNAL_ANALOG_DELSIG_0_ANALOG_CONVERT_VOLTS,
    .analog_gain_numerator = BATTERY_INTERNAL_ANALOG_DELSIG_0_ANALOG_GAIN_NUMERATOR,
    .analog_gain_denominator = BATTERY_INTERNAL_ANALOG_DELSIG_0_ANALOG_GAIN_DENOMINATOR,
    .readings = &battery_internal_0_readings,
    .labels = &battery_internal_0_labels,
    .invalid = &battery_internal_0_invalid
};

// Decagon GS3 TTL
char *gs3_ttl_0_labels[GS3_TTL_0_NVARS] = {GS3_TTL_0_LABEL_0, GS3_TTL_0_LABEL_1, GS3_TTL_0_LABEL_2, GS3_TTL_0_LABEL_3};
float gs3_ttl_0_readings[GS3_TTL_0_NVARS] = {GS3_TTL_0_DEFAULT_0, GS3_TTL_0_DEFAULT_1, GS3_TTL_0_DEFAULT_2, GS3_TTL_0_DEFAULT_3};
float gs3_ttl_0_invalid[GS3_TTL_0_NVARS] = {GS3_TTL_0_INVALID_0, GS3_TTL_0_INVALID_1, GS3_TTL_0_INVALID_2, GS3_TTL_0_INVALID_3};
char *gs3_ttl_0_str_starts[GS3_TTL_0_NVARS] = {GS3_TTL_0_STR_START_0, GS3_TTL_0_STR_START_1, GS3_TTL_0_STR_START_2, GS3_TTL_0_STR_START_3};
char *gs3_ttl_0_str_ends[GS3_TTL_0_NVARS] = {GS3_TTL_0_STR_END_0, GS3_TTL_0_STR_END_1, GS3_TTL_0_STR_END_2, GS3_TTL_0_STR_END_3};
static DeviceDict gs3_ttl_0 = 
{
    .baud = GS3_TTL_0_BAUD,
    .on_time = GS3_TTL_0_ON_TIME,
    .mux_term = GS3_TTL_0_GENERIC_UART_RX,
    .power_term = GS3_TTL_0_POWER,
    .nvars = GS3_TTL_0_NVARS,
    .readings = &gs3_ttl_0_readings,
    .labels = &gs3_ttl_0_labels,
    .invalid = &gs3_ttl_0_invalid,
    .str_starts = &gs3_ttl_0_str_starts,
    .str_ends = &gs3_ttl_0_str_ends
};

// Maxbotix MB7383_0
char *mb7383_ttl_0_labels[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_LABEL_0};
float mb7383_ttl_0_readings[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_DEFAULT_0};
float mb7383_ttl_0_invalid[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_INVALID_0};
char *mb7383_ttl_0_str_starts[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_STR_START_0};
char *mb7383_ttl_0_str_ends[MB7383_TTL_0_NVARS] = {MB7383_TTL_0_STR_END_0};
static DeviceDict mb7383_ttl_0 = 
{
    .baud = MB7383_TTL_0_BAUD,
    .on_time = MB7383_TTL_0_ON_TIME,
    .mux_term = MB7383_TTL_0_GENERIC_UART_RX,
    .power_term = MB7383_TTL_0_POWER,
    .nvars = MB7383_TTL_0_NVARS,
    .readings = &mb7383_ttl_0_readings,
    .labels = &mb7383_ttl_0_labels,
    .invalid = &mb7383_ttl_0_invalid,
    .str_starts = &mb7383_ttl_0_str_starts,
    .str_ends = &mb7383_ttl_0_str_ends
};

// Maxbotix MB7383_1
char *mb7383_ttl_1_labels[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_LABEL_0};
float mb7383_ttl_1_readings[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_DEFAULT_0};
float mb7383_ttl_1_invalid[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_INVALID_0};
char *mb7383_ttl_1_str_starts[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_STR_START_0};
char *mb7383_ttl_1_str_ends[MB7383_TTL_1_NVARS] = {MB7383_TTL_1_STR_END_0};
static DeviceDict mb7383_ttl_1 = 
{
    .baud = MB7383_TTL_1_BAUD,
    .on_time = MB7383_TTL_1_ON_TIME,
    .mux_term = MB7383_TTL_1_GENERIC_UART_RX,
    .power_term = MB7383_TTL_1_POWER,
    .nvars = MB7383_TTL_1_NVARS,
    .readings = &mb7383_ttl_1_readings,
    .labels = &mb7383_ttl_1_labels,
    .invalid = &mb7383_ttl_1_invalid,
    .str_starts = &mb7383_ttl_1_str_starts,
    .str_ends = &mb7383_ttl_1_str_ends
};

#endif
/* [] END OF FILE */
