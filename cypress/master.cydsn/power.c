#include "peripheral_globals.h"
#if POWER_ACTIVATED
#include <project.h>

uint8 power_toggle(uint8 on_off, uint8 which_demux_terminal){
    power_signal_Write(on_off);
    power_demux_controller_Write(which_demux_terminal);
    return 1u;
}

#endif
/* [] END OF FILE */
