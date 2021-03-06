/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2018, Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the Simba project.
 */

#ifndef __DRIVERS_UART_PORT_H__
#define __DRIVERS_UART_PORT_H__

#include <io.h>

/*
 * ESP8266 supports 5/6/7/8 data bits, N/E/O parity, 1/1.5/2 stop bits
 */
#define ESP_UART_DATA_BITS_5  (0x00 << ESP8266_UART_CONF0_BIT_NUM_POS)
#define ESP_UART_DATA_BITS_6  (0x01 << ESP8266_UART_CONF0_BIT_NUM_POS)
#define ESP_UART_DATA_BITS_7  (0x02 << ESP8266_UART_CONF0_BIT_NUM_POS)
#define ESP_UART_DATA_BITS_8  (0x03 << ESP8266_UART_CONF0_BIT_NUM_POS)
#define ESP_UART_PARITY_N     (0x00 << ESP8266_UART_CONF0_PARITY_POS)
#define ESP_UART_PARITY_E     (0x02 << ESP8266_UART_CONF0_PARITY_POS)
#define ESP_UART_PARITY_O     (0x03 << ESP8266_UART_CONF0_PARITY_POS)
#define ESP_UART_STOP_BITS_1  (0x01 << ESP8266_UART_CONF0_STOP_BIT_NUM_POS)
#define ESP_UART_STOP_BITS_15 (0x02 << ESP8266_UART_CONF0_STOP_BIT_NUM_POS)
#define ESP_UART_STOP_BITS_2  (0x03 << ESP8266_UART_CONF0_STOP_BIT_NUM_POS)
#define UART_PORT_FRAME_FORMAT_5N1   (ESP_UART_DATA_BITS_5 \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_5N15  (ESP_UART_DATA_BITS_5 \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_5N2   (ESP_UART_DATA_BITS_5 \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_5O1   (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_5O15  (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_5O2   (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_5E1   (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_5E15  (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_5E2   (ESP_UART_DATA_BITS_5  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_6N1   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_6N15  (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_6N2   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_6O1   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_6O15  (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_6O2   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_6E1   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_6E15  (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_6E2   (ESP_UART_DATA_BITS_6  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_7N1   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_7N15  (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_7N2   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_7O1   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_7O15  (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_7O2   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_7E1   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_7E15  (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_7E2   (ESP_UART_DATA_BITS_7  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_8N1   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_8N15  (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_8N2   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_N | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_8O1   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_8O15  (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_8O2   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_O | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_8E1   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_1)
#define UART_PORT_FRAME_FORMAT_8E15  (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_15)
#define UART_PORT_FRAME_FORMAT_8E2   (ESP_UART_DATA_BITS_8  \
        | ESP_UART_PARITY_E | ESP_UART_STOP_BITS_2)
#define UART_PORT_FRAME_FORMAT_DEFAULT UART_PORT_FRAME_FORMAT_8N1

struct uart_device_t {
    struct uart_driver_t *drv_p;         /* Current started driver. */
    volatile struct esp8266_uart_t *regs_p;
};

struct uart_driver_t {
    struct queue_t base;
    struct uart_device_t *dev_p;
    struct mutex_t mutex;
    const char *txbuf_p;
    size_t txsize;
    struct thrd_t *thrd_p;
    long baudrate;
    int format;
};

#endif
