/**
 * @file main.c
 * @version 1.1.0
 *
 * @section License
 * Copyright (C) 2014-2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"

static char stat[128];
static char buf[32];

int main()
{
    struct uart_driver_t uart;
    uint8_t flags = 3;

    sys_start();
    uart_module_init();

    uart_init(&uart, &uart_device[0], 38400, buf, sizeof(buf));
    uart_start(&uart);

    uart_write(&uart, stat, sprintf(stat, "stat: %x", flags));

    while (1);

    uart_stop(&uart);

    return (0);
}
