#ifndef LWIP_PING_H
#define LWIP_PING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/ip_addr.h"

void ping_init(const ip_addr_t* ping_addr);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_PING_H */
