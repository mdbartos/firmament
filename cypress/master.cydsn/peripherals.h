#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#define MB7383_TTL_0_POWER_TERMINAL 0u
#define MB7383_TTL_0_UART_MUX_TERMINAL 0u
#define MB7383_TTL_0_UART_BAUD 9600u
#define MB7383_TTL_0_ON_TIME 800u
#define MB7383_TTL_0_REGEX "\rR([0-9]+)\r"
#define MB7383_TTL_0_BUFFER_LEN 5
#define MB7383_TTL_0_NVARS 1
#define MB7383_TTL_0_STR_START_0 "TempI\rR"
#define MB7383_TTL_0_STR_END_0 "\r"
#define MB7383_TTL_0_INVALID_0 9999
#define MB7383_TTL_0_DEFAULT_0 -9999
#define MB7383_TTL_0_LABEL_0 "maxbotix_depth"
    
#define MB7383_TTL_1_POWER_TERMINAL 1u
#define MB7383_TTL_1_UART_MUX_TERMINAL 1u
#define MB7383_TTL_1_UART_BAUD 9600u
#define MB7383_TTL_1_ON_TIME 800u
#define MB7383_TTL_1_REGEX "\rR([0-9]+)\r"
#define MB7383_TTL_1_BUFFER_LEN 5
#define MB7383_TTL_1_NVARS 1
#define MB7383_TTL_1_STR_START_0 "TempI\rR"
#define MB7383_TTL_1_STR_END_0 "\r"
#define MB7383_TTL_1_INVALID_0 9999
#define MB7383_TTL_1_DEFAULT_0 -9999
#define MB7383_TTL_1_LABEL_0 "maxbotix_2_depth"
    
#define GS3_TTL_0_POWER_TERMINAL 2u
#define GS3_TTL_0_UART_MUX_TERMINAL 2u
#define GS3_TTL_0_UART_BAUD 1200u
#define GS3_TTL_0_ON_TIME 800u
#define GS3_TTL_0_REGEX "\rR([0-9]+)\r"
#define GS3_TTL_0_BUFFER_LEN 5
#define GS3_TTL_0_NVARS 4
#define GS3_TTL_0_STR_START_0 "\t"
#define GS3_TTL_0_STR_START_1 " "
#define GS3_TTL_0_STR_START_2 " "
#define GS3_TTL_0_STR_START_3 "w"
#define GS3_TTL_0_STR_END_0 " "
#define GS3_TTL_0_STR_END_1 " "
#define GS3_TTL_0_STR_END_2 "\r"
#define GS3_TTL_0_STR_END_3 "\r\n"
#define GS3_TTL_0_INVALID_0 9999
#define GS3_TTL_0_INVALID_1 9999
#define GS3_TTL_0_INVALID_2 9999
#define GS3_TTL_0_INVALID_3 9999
#define GS3_TTL_0_DEFAULT_0 -9999
#define GS3_TTL_0_DEFAULT_1 -9999
#define GS3_TTL_0_DEFAULT_2 -9999
#define GS3_TTL_0_DEFAULT_3 -9999
#define GS3_TTL_0_LABEL_0 "decagon_soil_dielec"
#define GS3_TTL_0_LABEL_1 "decagon_soil_temp"
#define GS3_TTL_0_LABEL_2 "decagon_soil_conduct"
#define GS3_TTL_0_LABEL_3 "decagon_checksum"

#define BATTERY_INTERNAL_0_POWER_TERMINAL 3u
#define BATTERY_INTERNAL_0_ANALOG_MUX_TERMINAL 0u
#define BATTERY_INTERNAL_0_ON_TIME 800u
#define BATTERY_INTERNAL_0_ANALOG_CONVERT_VOLTS 1u
#define BATTERY_INTERNAL_0_ANALOG_GAIN_NUMERATOR 11.0
#define BATTERY_INTERNAL_0_ANALOG_GAIN_DENOMINATOR 1.0
#define BATTERY_INTERNAL_0_NVARS 1
#define BATTERY_INTERNAL_0_INVALID_0 9999
#define BATTERY_INTERNAL_0_DEFAULT_0 -9999
#define BATTERY_INTERNAL_0_LABEL_0 "v_bat"
    
#define ATLAS_DO_I2C_0_POWER_TERMINAL 4u
#define ATLAS_DO_I2C_0_ON_TIME 800u
#define ATLAS_DO_I2C_0_BUFFER_LEN 10
#define ATLAS_DO_I2C_0_NVARS 1
#define ATLAS_DO_I2C_0_SLAVE_ADDRESS 97    
#define ATLAS_DO_I2C_0_DELAY 1000u
#define ATLAS_DO_I2C_0_COMMAND_BUFFER_SIZE 7
#define ATLAS_DO_I2C_0_READ_COMMAND "R"
#define ATLAS_DO_I2C_0_AFFIRM_RESPONSE_CODE 1u
#define ATLAS_DO_I2C_0_STR_START_0 "\1"
#define ATLAS_DO_I2C_0_STR_END_0 ""
#define ATLAS_DO_I2C_0_INVALID_0 9999
#define ATLAS_DO_I2C_0_DEFAULT_0 -9999
#define ATLAS_DO_I2C_0_LABEL_0 "atlas_dissolved_oxygen"
    
#endif
/* [] END OF FILE */
