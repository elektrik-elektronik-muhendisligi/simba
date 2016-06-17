/**
 * @file lwipopts.h
 * @version 0.7.0
 *
 * @section License
 * Copyright (C) 2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERSOCKTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "stdlib.h"

/* These defines should not be changed by the user. The Simba port of
 * the lwIP stack requires them to have given values. */
#define NO_SYS                      0
#define SYS_LIGHTWEIGHT_PROT        1
#define LWIP_SOCKET                 0
#define LWIP_COMPAT_SOCKETS         0
#define LWIP_POSIX_SOCKETS_IO_NAMES 0
#define LWIP_PREFIX_BYTEORDER_FUNCS

/* Architecture defiens that the user hopefully does not have to
 * change, but may redefine. */

#ifndef TCPIP_THREAD_NAME
#    define TCPIP_THREAD_NAME           "tcpip"
#endif

#ifndef TCPIP_THREAD_STACKSIZE
#    define TCPIP_THREAD_STACKSIZE      1024
#endif

#ifndef TCPIP_MBOX_SIZE
#    define TCPIP_MBOX_SIZE             8
#endif

#ifndef MEM_ALIGNMENT
#    define MEM_ALIGNMENT               4
#endif

#ifndef LWIP_RAND
#    define LWIP_RAND()                 rand()
#endif

#ifndef LWIP_CHECKSUM_ON_COPY
#    define LWIP_CHECKSUM_ON_COPY       0
#endif

/* TCP/IP stack configuration. */

#ifndef LWIP_RAW
#    define LWIP_RAW                    0
#endif

#ifndef DEFAULT_TCP_RECVMBOX_SIZE
#    define DEFAULT_TCP_RECVMBOX_SIZE   8
#endif

#ifndef DEFAULT_UDP_RECVMBOX_SIZE
#    define DEFAULT_UDP_RECVMBOX_SIZE   8
#endif

#ifndef DEFAULT_RAW_RECVMBOX_SIZE
#    define DEFAULT_RAW_RECVMBOX_SIZE   8
#endif

#ifndef DEFAULT_ACCEPTMBOX_SIZE
#    define DEFAULT_ACCEPTMBOX_SIZE     8
#endif

#ifndef MEM_SIZE
#    define MEM_SIZE                    8000
#endif

#ifndef MEMP_NUM_SYS_TIMEOUT
#    define MEMP_NUM_SYS_TIMEOUT        16
#endif

#ifndef PBUF_POOL_SIZE
#    define PBUF_POOL_SIZE              8
#endif

#ifndef MEMP_NUM_TCP_PCB_LISTEN
#    define MEMP_NUM_TCP_PCB_LISTEN     4
#endif

#ifndef MEMP_NUM_TCP_PCB
#    define MEMP_NUM_TCP_PCB            4
#endif

#ifndef MEMP_NUM_UDP_PCB
#    define MEMP_NUM_UDP_PCB            4
#endif

#ifndef MEMP_NUM_PBUF
#    define MEMP_NUM_PBUF               8
#endif

#ifndef MEMP_NUM_NETBUF
#    define MEMP_NUM_NETBUF             8
#endif

#ifndef TCP_QUEUE_OOSEQ
#    define TCP_QUEUE_OOSEQ             0
#endif

#ifndef TCP_OVERSIZE
#    define TCP_OVERSIZE                0
#endif

#ifndef LWIP_DHCP
#    define LWIP_DHCP                   1
#endif

#ifndef LWIP_DNS
#    define LWIP_DNS                    1
#endif

#ifndef LWIP_IGMP
#    define LWIP_IGMP                   1
#endif

#ifndef LWIP_SO_RCVTIMEO
#    define LWIP_SO_RCVTIMEO            1
#endif

#ifndef LWIP_TCP_KEEPALIVE
#    define LWIP_TCP_KEEPALIVE          1
#endif

#ifndef TCP_MSS
#    define TCP_MSS                     1460
#endif

#ifndef TCP_SND_BUF
#    define TCP_SND_BUF                 (2 * TCP_MSS)
#endif

#ifndef TCP_WND
#    define TCP_WND                     (2 * TCP_MSS)
#endif

#ifndef IP_SOF_BROADCAST
#    define IP_SOF_BROADCAST            1
#endif

#ifndef IP_SOF_BROADCAST_RECV
#    define IP_SOF_BROADCAST_RECV       1
#endif

#ifndef LWIP_BROADCAST_PING
#    define LWIP_BROADCAST_PING         1
#endif

#ifndef LWIP_NETIF_HOSTNAME
#    define LWIP_NETIF_HOSTNAME         1
#endif

#ifndef LWIP_NETIF_STATUS_CALLBACK
#    define LWIP_NETIF_STATUS_CALLBACK  1
#endif

#ifndef LWIP_NETIF_LINK_CALLBACK
#    define LWIP_NETIF_LINK_CALLBACK    1
#endif


/* Debugging. */

#ifndef LWIP_NOASSERT
#    define LWIP_NOASSERT               1
#endif

#ifndef LWIP_STATS
#    define LWIP_STATS                  0
#endif

//#define LWIP_DEBUG

#ifndef UDP_LPC_EMAC
#    define UDP_LPC_EMAC                LWIP_DBG_OFF
#endif

#ifndef SYS_DEBUG
#    define SYS_DEBUG                   LWIP_DBG_OFF
#endif

#ifndef PPP_DEBUG
#    define PPP_DEBUG                   LWIP_DBG_OFF
#endif

#ifndef IP_DEBUG
#    define IP_DEBUG                    LWIP_DBG_OFF
#endif

#ifndef MEM_DEBUG
#    define MEM_DEBUG                   LWIP_DBG_OFF
#endif

#ifndef MEMP_DEBUG
#    define MEMP_DEBUG                  LWIP_DBG_OFF
#endif

#ifndef PBUF_DEBUG
#    define PBUF_DEBUG                  LWIP_DBG_OFF
#endif

#ifndef API_LIB_DEBUG
#    define API_LIB_DEBUG               LWIP_DBG_OFF
#endif

#ifndef API_MSG_DEBUG
#    define API_MSG_DEBUG               LWIP_DBG_OFF
#endif

#ifndef TCPIP_DEBUG
#    define TCPIP_DEBUG                 LWIP_DBG_OFF
#endif

#ifndef SOCKETS_DEBUG
#    define SOCKETS_DEBUG               LWIP_DBG_OFF
#endif

#ifndef TCP_DEBUG
#    define TCP_DEBUG                   LWIP_DBG_OFF
#endif

#ifndef TCP_INPUT_DEBUG
#    define TCP_INPUT_DEBUG             LWIP_DBG_OFF
#endif

#ifndef TCP_FR_DEBUG
#    define TCP_FR_DEBUG                LWIP_DBG_OFF
#endif

#ifndef TCP_RTO_DEBUG
#    define TCP_RTO_DEBUG               LWIP_DBG_OFF
#endif

#ifndef TCP_CWND_DEBUG
#    define TCP_CWND_DEBUG              LWIP_DBG_OFF
#endif

#ifndef TCP_WND_DEBUG
#    define TCP_WND_DEBUG               LWIP_DBG_OFF
#endif

#ifndef TCP_OUTPUT_DEBUG
#    define TCP_OUTPUT_DEBUG            LWIP_DBG_OFF
#endif

#ifndef TCP_RST_DEBUG
#    define TCP_RST_DEBUG               LWIP_DBG_OFF
#endif

#ifndef TCP_QLEN_DEBUG
#    define TCP_QLEN_DEBUG              LWIP_DBG_OFF
#endif

#ifndef ETHARP_DEBUG
#    define ETHARP_DEBUG                LWIP_DBG_OFF
#endif

#ifndef NETIF_DEBUG
#    define NETIF_DEBUG                 LWIP_DBG_OFF
#endif

#ifndef DHCP_DEBUG
#    define DHCP_DEBUG                  LWIP_DBG_OFF
#endif

#endif