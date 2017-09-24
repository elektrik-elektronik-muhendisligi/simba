/**
 * @section License
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2017, Erik Moqvist
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

#include "simba.h"

extern void socket_stub_init(void);
extern void socket_stub_input(void *buf_p, size_t size);
extern void socket_stub_output(void *buf_p, size_t size);

static struct socket_t socket;
static struct http_websocket_server_t server;

#if defined(ARCH_LINUX)
static uint8_t buf[131072];
#else
static uint8_t buf[256];
#endif

static int test_init(void)
{
    socket_stub_init();

    /* The socket is uninitialized in the test suite since the socket
       stub does not use it. */
    BTASSERT(http_websocket_server_init(&server, &socket) == 0);

    return (0);
}

static int test_handshake(void)
{
    struct http_server_request_t request;

    /* Initialize the request.*/
    request.action = http_server_request_action_get_t;
    request.headers.sec_websocket_key.present = 1;
    strcpy(request.headers.sec_websocket_key.value, "");

    /* Perform the handshake. */
    BTASSERT(http_websocket_server_handshake(&server,
                                             &request) == 0);
    socket_stub_output(buf, 129);
    BTASSERT(strcmp((char *)buf,
                    "HTTP/1.1 101 Switching Protocols\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Accept: Kfh9QIsMVZcl6xEPYxPHzW8SZ8w=\r\n"
                    "\r\n") == 0);

    return (0);
}

static int test_handshake_key_missing(void)
{
    struct http_server_request_t request;

    /* Initialize the request.*/
    request.action = http_server_request_action_get_t;
    request.headers.sec_websocket_key.present = 0;

    /* Perform the handshake. */
    BTASSERT(http_websocket_server_handshake(&server,
                                             &request) == -1);

    return (0);
}

static int test_handshake_bad_action(void)
{
    struct http_server_request_t request;

    /* Initialize the request.*/
    request.action = http_server_request_action_get_t + 1;
    request.headers.sec_websocket_key.present = 1;
    strcpy(request.headers.sec_websocket_key.value, "");

    /* Perform the handshake. */
    BTASSERT(http_websocket_server_handshake(&server,
                                             &request) == -1);

    return (0);
}

static int test_read(void)
{
    int type;

    /* Prepare socket input with 1 length byte. */
    buf[0] = 0x81; /* FIN & TEXT. */
    buf[1] = 0x83; /* MASK and 1 byte payload length. */
    buf[2] = 0x01; /* Masking key 0. */
    buf[3] = 0x02; /* Masking key 1. */
    buf[4] = 0x03; /* Masking key 2. */
    buf[5] = 0x04; /* Masking key 3. */
    buf[6] = 'g';  /* Payload 0. */
    buf[7] = 'm';  /* Payload 1. */
    buf[8] = 'l';  /* Payload 2. */
    socket_stub_input(buf, 9);

    BTASSERT(http_websocket_server_read(&server,
                                        &type,
                                        buf,
                                        sizeof(buf)) == 3);
    BTASSERT(buf[0] == 'f');
    BTASSERT(buf[1] == 'o');
    BTASSERT(buf[2] == 'o');

    /* Prepare socket input with 2 length byte. */
    buf[0] = 0x81; /* FIN & TEXT. */
    buf[1] = 0xfe; /* MASK and 2 bytes payload length. */
    buf[2] = 0x00; /* Payload length 0. */
    buf[3] = 0x03; /* Payload length 1. */
    buf[4] = 0x00; /* Masking key 0. */
    buf[5] = 0x00; /* Masking key 1. */
    buf[6] = 0x00; /* Masking key 2. */
    buf[7] = 0x00; /* Masking key 3. */
    buf[8] = 'b';  /* Payload 0. */
    buf[9] = 'a';  /* Payload 1. */
    buf[10] = 'r'; /* Payload 2. */
    socket_stub_input(buf, 11);

    BTASSERT(http_websocket_server_read(&server,
                                        &type,
                                        buf,
                                        sizeof(buf)) == 3);
    BTASSERT(buf[0] == 'b');
    BTASSERT(buf[1] == 'a');
    BTASSERT(buf[2] == 'r');

    /* Prepare socket input with 8 length byte. */
    buf[0] = 0x81;  /* FIN & TEXT. */
    buf[1] = 0xff;  /* MASK and 8 bytes payload length. */
    buf[2] = 0x00;  /* Payload length 0. */
    buf[3] = 0x00;  /* Payload length 1. */
    buf[4] = 0x00;  /* Payload length 2. */
    buf[5] = 0x00;  /* Payload length 3. */
    buf[6] = 0x00;  /* Payload length 4. */
    buf[7] = 0x00;  /* Payload length 5. */
    buf[8] = 0x00;  /* Payload length 6. */
    buf[9] = 0x03;  /* Payload length 7. */
    buf[10] = 0x00; /* Masking key 0. */
    buf[11] = 0x00; /* Masking key 1. */
    buf[12] = 0x00; /* Masking key 2. */
    buf[13] = 0x00; /* Masking key 3. */
    buf[14] = 'f';  /* Payload 0. */
    buf[15] = 'i';  /* Payload 1. */
    buf[16] = 'e';  /* Payload 2. */
    socket_stub_input(buf, 17);

    BTASSERT(http_websocket_server_read(&server,
                                        &type,
                                        buf,
                                        sizeof(buf)) == 3);
    BTASSERT(buf[0] == 'f');
    BTASSERT(buf[1] == 'i');
    BTASSERT(buf[2] == 'e');

    /* Prepare socket input with 1 length byte. */
    buf[0] = 0x81; /* FIN & TEXT. */
    buf[1] = 0x83; /* MASK and 1 byte payload length. */
    buf[2] = 0x00; /* Masking key 0. */
    buf[3] = 0x00; /* Masking key 1. */
    buf[4] = 0x00; /* Masking key 2. */
    buf[5] = 0x00; /* Masking key 3. */
    buf[6] = 'f';  /* Payload 0. */
    buf[7] = 'o';  /* Payload 1. */
    buf[8] = 'o';  /* Payload 2. */
    socket_stub_input(buf, 9);

    /* Read only two of the three bytes. The third byte should be
       discarded. */
    BTASSERT(http_websocket_server_read(&server,
                                        &type,
                                        buf,
                                        2) == 2);
    BTASSERT(buf[0] == 'f');
    BTASSERT(buf[1] == 'o');

    /* Prepare socket input with 1 length byte. */
    buf[0] = 0x81; /* FIN & TEXT. */
    buf[1] = 0x83; /* MASK and 1 byte payload length. */
    buf[2] = 0x00; /* Masking key 0. */
    buf[3] = 0x00; /* Masking key 1. */
    buf[4] = 0x00; /* Masking key 2. */
    buf[5] = 0x00; /* Masking key 3. */
    buf[6] = 'f';  /* Payload 0. */
    buf[7] = 'o';  /* Payload 1. */
    buf[8] = 'o';  /* Payload 2. */
    socket_stub_input(buf, 9);

    BTASSERT(http_websocket_server_read(&server,
                                        &type,
                                        buf,
                                        sizeof(buf)) == 3);
    BTASSERT(buf[0] == 'f');
    BTASSERT(buf[1] == 'o');
    BTASSERT(buf[2] == 'o');

    return (0);
}

static int test_write(void)
{
    buf[0] = 'f';
    buf[1] = 'o';
    buf[2] = 'o';

    BTASSERT(http_websocket_server_write(&server,
                                         HTTP_TYPE_BINARY,
                                         buf,
                                         3) == 3);

    /* Verify the output data. */
    socket_stub_output(buf, 2 + 3);
    BTASSERT(buf[0] == 0x82); /* FIN & BINARY. */
    BTASSERT(buf[1] == 0x03); /* 3 bytes of payload. */
    BTASSERT(buf[2] == 'f');  /* Payload 0. */
    BTASSERT(buf[3] == 'o');  /* Payload 1. */
    BTASSERT(buf[4] == 'o');  /* Payload 2. */

    buf[0] = 'b';
    buf[1] = 'a';
    buf[2] = 'r';

    BTASSERT(http_websocket_server_write(&server,
                                         HTTP_TYPE_BINARY,
                                         buf,
                                         126) == 126);

    /* Prepare socket input with 2 length byte. */
    socket_stub_output(buf, 4 + 126);
    BTASSERT(buf[0] == 0x82); /* FIN & BINARY. */
    BTASSERT(buf[1] == 0x7e); /* 2 bytes payload length. */
    BTASSERT(buf[2] == 0x00); /* Payload length 0. */
    BTASSERT(buf[3] == 0x7e); /* Payload length 1. */
    BTASSERT(buf[4] == 'b');  /* Payload 0. */
    BTASSERT(buf[5] == 'a');  /* Payload 1. */
    BTASSERT(buf[6] == 'r');  /* Payload 2. */

#if defined(ARCH_LINUX)

    buf[0] = 'f';
    buf[1] = 'i';
    buf[2] = 'e';

    BTASSERT(http_websocket_server_write(&server,
                                         HTTP_TYPE_BINARY,
                                         buf,
                                         65536) == 65536);

    /* Prepare socket input with 8 length byte. */
    socket_stub_output(buf, 10 + 65536);
    BTASSERT(buf[0] == 0x82); /* FIN & BINARY. */
    BTASSERT(buf[1] == 0x7f); /* 8 bytes payload length. */
    BTASSERT(buf[2] == 0x00); /* Payload length 0. */
    BTASSERT(buf[3] == 0x00); /* Payload length 1. */
    BTASSERT(buf[4] == 0x00); /* Payload length 2. */
    BTASSERT(buf[5] == 0x00); /* Payload length 3. */
    BTASSERT(buf[6] == 0x00); /* Payload length 4. */
    BTASSERT(buf[7] == 0x01); /* Payload length 5. */
    BTASSERT(buf[8] == 0x00); /* Payload length 6. */
    BTASSERT(buf[9] == 0x00); /* Payload length 7. */
    BTASSERT(buf[10] == 'f'); /* Payload 0. */
    BTASSERT(buf[11] == 'i'); /* Payload 1. */
    BTASSERT(buf[12] == 'e'); /* Payload 2. */

#endif

    return (0);
}

int main()
{
    struct harness_testcase_t harness_testcases[] = {
        { test_init, "test_init" },
        { test_handshake, "test_handshake" },
        { test_handshake_key_missing, "test_handshake_key_missing" },
        { test_handshake_bad_action, "test_handshake_bad_action" },
        { test_read, "test_read" },
        { test_write, "test_write" },
        { NULL, NULL }
    };

    sys_start();

    harness_run(harness_testcases);

    return (0);
}
