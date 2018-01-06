#include "peripheral_globals.h"
#if (GENERIC_UART_ACTIVATED && POWER_ACTIVATED)
#include "generic_uart_control.h"
#include "strlib.h"
#include "power.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static const uint32_t MASTER_CLOCK_FREQ = 24000000u;  //  24 MHz

// The buffer and index are dependent on eachother. This buffer is implemented
// as a circular buffer to avoid overflow.
static char generic_uart_buf[257] = {'\0'};
static uint8_t generic_uart_buf_idx = 0u;

void generic_uart_start() {
    generic_uart_Start();
    generic_uart_rx_isr_StartEx(generic_uart_rx_isr);
}

void generic_uart_stop() {
    generic_uart_rx_isr_Stop();
    generic_uart_Stop();
}

void generic_uart_select_input(uint8 mux_terminal){
    generic_uart_mux_controller_Write(mux_terminal);
}

// Rounds any positive float to the nearest whole number.
inline static unsigned int pos_round(const float val) { return val + 0.5f; }

// The equation to set the baud rate is as follows:
// divider = source_clock_frequency / (8 * desired_baud_rate)
//
// Then set the divider for the digital clock using the calculated value.
void generic_uart_set_baud(const uint32_t baud) {
    const uint32_t desired_clock = 8 * baud;
    const uint16_t divider =
        pos_round((float) MASTER_CLOCK_FREQ / desired_clock);

    generic_uart_clock_SetDividerValue(divider);
}

char* generic_uart_get_string() { return generic_uart_buf; }

size_t generic_uart_get_string_size() {
    return generic_uart_buf_idx;  // equivalent to strlen(sensors_uart_buf)
}

void generic_uart_clear_string() {
    generic_uart_ClearRxBuffer();
    memset(generic_uart_buf, '\0', sizeof(generic_uart_buf));
    generic_uart_buf_idx = 0u;
}

/**
 * @brief Parse raw UART received string from any sensor into @p reading.
 *
 * @param reading Structure to store results into. Depth in millimeters.
 * @param str Raw UART received string.
 */
int generic_uart_parse_reading(DeviceDict device, char *str){
    float reading = 0;
    char reading_str[MAX_EXTRACT_BUFFER_SIZE] = {'\0'};
    char *search_start = str;
    if (device.skipchars){
        search_start += device.skipchars;
    }
    int i = 0;
    for (i = 0; i < device.nvars; i++){
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

int generic_uart_get_reading(DeviceDict device){
    generic_uart_clear_string();
    generic_uart_set_baud(device.baud);
    generic_uart_select_input(device.mux_term);
    generic_uart_start();
    power_toggle(1u, device.power_term);
    CyDelay(device.on_time);
    power_toggle(0u, device.power_term);
    generic_uart_stop();
    char *uart_string = generic_uart_get_string();
    generic_uart_parse_reading(device, uart_string);
    return 1u;
}

int generic_uart_zip(char *labels[], float readings[], DeviceDict device, int *array_ix, int max_size){
    int iter = 0u;
    if (*array_ix + device.nvars >= max_size){
        return *array_ix;
    }
    for (iter=0; iter < device.nvars; iter++)
    {
        labels[*array_ix] = (*device.labels)[iter];
        readings[*array_ix] = (*device.readings)[iter];
        *array_ix += 1;
    }
    return *array_ix;
}
                                    
CY_ISR(generic_uart_rx_isr) {
    // hold the next char in the rx register as a temporary variable
    char rx_char = generic_uart_GetChar();

    // store the char in sensors_uart_buf
    if (rx_char) {
        // unsigned ints don't `overflow`, they reset at 0 if they are
        // incremented one more than it's max value. It will be obvious if an
        // `overflow` occurs
        generic_uart_buf[generic_uart_buf_idx++] = rx_char;
    }
}

#endif
/* [] END OF FILE */
