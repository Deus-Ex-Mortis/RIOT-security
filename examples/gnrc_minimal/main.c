/*
 * Copyright (C) 2015 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Showing minimum memory footprint of gnrc network stack
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include <stdio.h>

#include "msg.h"
#include "net/ipv6/addr.h"
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/netreg.h"
#include "thread.h"
#include "net/gnrc/pktbuf.h"

int main(void)
{

    puts("RIOT network stack example application");

    /* get interfaces and print their addresses */
    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif))) {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs,
                                  sizeof(ipv6_addrs));

        if (res < 0) {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++) {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("My address is %s\n", ipv6_addr);
        }
    }

	msg_t msg_queue[4];
	msg_init_queue(msg_queue, 4);
	gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(8888, thread_getpid());
	gnrc_netreg_register(GNRC_NETTYPE_UDP, &server);
	msg_t msg;
	msg_receive(&msg);
	gnrc_pktsnip_t *pkt = (gnrc_pktsnip_t *)msg.content.ptr;
	gnrc_pktbuf_release(pkt);

    /* main thread exits */
    return 0;
}
