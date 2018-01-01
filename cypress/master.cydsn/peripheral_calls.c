#include "peripheral_globals.h"
#include "peripheral_instances.h"
#include "strlib.h"
#include "public_vars.h"

#if GENERIC_UART_ACTIVATED
    #include "generic_uart_control.h"
#endif

#if ANALOG_DELSIG_ACTIVATED
    #include "analog_delsig_control.h"
#endif

#if I2C_ACTIVATED
    #include "i2c_control.h"
#endif

char *labels[MAIN_BUFFER_LEN] = {0};
float readings[MAIN_BUFFER_LEN] = {0};
int array_ix = 0u;

uint8 run_peripherals(){
    generic_uart_get_reading(mb7383_ttl_0);
    generic_uart_get_reading(gs3_ttl_0);
    analog_delsig_get_reading(battery_internal_0);
    return 1u;
}

uint8 zip_peripherals(){
    zip_measurements(labels, readings, mb7383_ttl_0, &array_ix, MAIN_BUFFER_LEN);
    zip_measurements(labels, readings, gs3_ttl_0, &array_ix, MAIN_BUFFER_LEN);
    zip_measurements(labels, readings, battery_internal_0, &array_ix, MAIN_BUFFER_LEN);
    array_ix = 0u;
    return 1u;
}

/* [] END OF FILE */
