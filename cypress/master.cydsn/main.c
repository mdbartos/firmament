#include <project.h>
#include "peripherals.h"
#include "generic_uart_control.h"
#include "mb7383_ttl.h"

int main(void)
{
    CyGlobalIntEnable;

    for(;;)
    {
        get_mb7383_reading();
    }
    return 1u;
}

/* [] END OF FILE */
