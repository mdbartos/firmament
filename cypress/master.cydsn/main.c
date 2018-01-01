#include <project.h>
#include "influxdb.h"
#include "peripheral_calls.h"
#include "public_vars.h"


char send_buffer[SEND_BUFFER_LEN] = {'\0'};

int main(void)
{
    CyGlobalIntEnable;
    
    for(;;)
    {
        run_peripherals();
        zip_peripherals();
        construct_influxdb_body(send_buffer, labels, readings, MAIN_BUFFER_LEN);
    }
    return 1u;
}

/* [] END OF FILE */
