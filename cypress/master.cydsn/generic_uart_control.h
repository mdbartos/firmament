/**
 * @file sensors_uart_control.h
 * @brief A collection of common patterns used to interface with the sensors
 * UART.
 * @author Ivan Mondragon
 * @version TODO
 * @date 2017-07-16
 */
#ifndef GENERIC_UART_CONTROL_H
#define GENERIC_UART_CONTROL_H

#include <project.h>
#include "peripherals.h"

#define MAX_EXTRACT_BUFFER_SIZE 16    

typedef struct {
    uint32_t baud;
    int on_time;
    uint8 mux_term;
    uint8 power_term;
    uint8 nvars;
    float (*readings)[];
    float (*invalid)[];
    char *(*labels)[];
    char *(*str_starts)[];
    char *(*str_ends)[];
} DeviceConfig;    
    
/**
 * @brief Starts the sensors UART with generic interrupt service.
 */
void generic_uart_start();

/**
 * @brief Stops the sensors UART and generic interrupt service.
 */
void generic_uart_stop();

/**
 * @brief Select multiplexer input on UART.
 */
void generic_uart_select_input(uint8 mux_terminal);

/**
 * @brief Sets the baud rate for the sensors uart.
 *
 * @param baud One of the standard baud rates. [1200, 2400, 4800, 9600, 14400,
 * 19200, 38400, 57600, 115200, 128000, or 256000]
 */
void generic_uart_set_baud(const uint32_t baud);

/**
 * @brief Get the uart received string.
 *
 * @return Pointer to the string in the buffer.
 */
char* generic_uart_get_string();

/**
 * @brief Get the size of the string in the buffer.
 *
 * @return Size of string in buffer.
 */
size_t generic_uart_get_string_size();

/**
 * @brief Clears internal buffer.
 */
void generic_uart_clear_string();

int generic_uart_parse_reading(DeviceConfig device, char *str);

int generic_uart_get_reading(DeviceConfig device);

CY_ISR_PROTO(generic_uart_rx_isr);

#endif

/* [] END OF FILE */