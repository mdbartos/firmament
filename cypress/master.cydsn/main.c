#include <project.h>
#include "peripherals.h"
#include "generic_uart_control.h"
#include "analog_delsig_control.h"
#include "mb7383_ttl_0.h"
#include "mb7383_ttl_1.h"
#include "gs3_ttl_0.h"
#include "battery_internal_0.h"
#include "strlib.h"
#include "influxdb.h"

// May need to combine all sensor structs into a single file

#define MAIN_BUFFER_LEN 16
#define SEND_BUFFER_LEN 2000

char send_buffer[SEND_BUFFER_LEN] = {'\0'};
char *labels[MAIN_BUFFER_LEN] = {0};
float readings[MAIN_BUFFER_LEN] = {0};
int array_ix = 0u;

int main(void)
{
    CyGlobalIntEnable;
    
    for(;;)
    {
        generic_uart_get_reading(mb7383_ttl_0);
        generic_uart_get_reading(mb7383_ttl_1);
        generic_uart_get_reading(gs3_ttl_0);
        analog_delsig_get_reading(battery_internal_0);
        zip_measurements(labels, readings, mb7383_ttl_0, &array_ix, MAIN_BUFFER_LEN);
        zip_measurements(labels, readings, mb7383_ttl_1, &array_ix, MAIN_BUFFER_LEN);
        zip_measurements(labels, readings, gs3_ttl_0, &array_ix, MAIN_BUFFER_LEN);
        zip_measurements(labels, readings, battery_internal_0, &array_ix, MAIN_BUFFER_LEN);
        construct_influxdb_body(send_buffer, labels, readings, MAIN_BUFFER_LEN);
        array_ix = 0u;
    }
    return 1u;
}

/* [] END OF FILE */
