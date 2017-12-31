#include "peripheral_globals.h"
#if I2C_ACTIVATED
#include "i2c_control.h"
#include <stdlib.h>
#include "device_dict.h"
#include "strlib.h"
#include "power.h"

#define I2C_MAX_ITER 100
#define I2C_READ_BUFFER_SIZE 20

// TODO: May not want to put read command into devicedict by itself
// TODO: I2C doesn't use an interrupt

int i2c_parse_reading(DeviceDict device, uint8 str[]){
    float reading = 0;
    char reading_str[I2C_READ_BUFFER_SIZE] = {'\0'};
    char *search_start = strchr((const char*)str, device.i2c_affirm_response_code);
    if (!search_start){
        return 0u;
    }
    int i = 0;
    for (i = 0; i < device.nvars; i++){
        // TODO: This parser is failing
        search_start = strextract(search_start, reading_str, (*device.str_starts)[i], (*device.str_ends)[i]);
        if (search_start){
            reading = strtof(reading_str, NULL);
            (*device.readings)[i] = reading;
        }
        else {
            return 0u;
        }
    }
    // Should check for valid
    return 1u;
}

uint8 i2c_get_reading(DeviceDict device){
    uint8 status;
    uint8 temp_status;
    int write_iter;
    int read_iter;
    int inner_iter;
    uint8 raw_reading[I2C_READ_BUFFER_SIZE] = {0};
    char *reading_start;
    
    // TODO: Move
    power_toggle(1u, device.power_term);
    CyDelay(1000);
    i2c_Wakeup();
    i2c_Start();
    CyDelay(500);
    
    for (write_iter=0; write_iter < I2C_MAX_ITER; write_iter ++){
        status = (i2c_MasterWriteBuf(device.i2c_slave_address, *(device.i2c_read_command), 
        device.i2c_command_buffer_size, i2c_MODE_COMPLETE_XFER) & i2c_MSTAT_WR_CMPLT);
        
        if (!status){
            break;
        }
    }
    CyDelay(device.i2c_delay);
   
    for(read_iter=0; read_iter < I2C_MAX_ITER; read_iter++){
            for (inner_iter=0; inner_iter < I2C_MAX_ITER; inner_iter++){
                status = (i2c_MasterReadBuf(device.i2c_slave_address, raw_reading, 
                    device.i2c_command_buffer_size, i2c_MODE_COMPLETE_XFER));
                CyDelay(100);
                temp_status = (status & i2c_MSTAT_RD_CMPLT);
                if (!status){
                    break;
                }
            }
        if (i2c_MasterGetReadBufSize() == device.i2c_command_buffer_size){
            break;
        }
    }

    i2c_parse_reading(device, raw_reading);
    
    memset(raw_reading, 0u, sizeof(raw_reading));
    // TODO: Move
    i2c_Sleep();
    power_toggle(0u, device.power_term);
    
    return 1u;
}

#endif
/* [] END OF FILE */
