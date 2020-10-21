#ifndef __METRICS_H__
#define __METRICS_H__

#include "lwipopts.h"
#include "lwip/ip_addr.h" 

#if !defined( FREERTOS_LWIP_METRICS_ENABLE ) || ( FREERTOS_LWIP_METRICS_ENABLE == 0 )
    #warning "FREERTOS_LWIP_METRICS_ENABLE is disabled."
#endif

#if !defined( LWIP_TCPIP_CORE_LOCKING_INPUT ) || ( LWIP_TCPIP_CORE_LOCKING_INPUT == 0 )
    #warning "The network metric will not be supported if LWIP_TCPIP_CORE_LOCKING_INPUT is disabled."
#endif


/* Extern veriables from LWIP */
extern struct netif sta_if, ap_if;

typedef struct connections{
    ip_addr_t addr;
    u16_t port;
    struct connections *next;
}connections_t;

typedef struct networkMetrics{
    uint32_t pktsIn;
    uint32_t pktsOut;
    uint32_t bytesIn;
    uint32_t bytesOut;
    uint16_t numOfActiveConnections;
    connections_t *remoteConnectionList;
    uint16_t numOfListenConnections;
    connections_t *listenConnectionList;
}networkMetrics_t;

extern networkMetrics_t _networkMetrics;	//for debug


#define LWIP_GET_TCP_PACKET_IN() (lwip_stats.mib2.ipinreceives)
#define LWIP_GET_TCP_PACKET_OUT() (lwip_stats.mib2.ipoutrequests + lwip_stats.mib2.ipforwdatagrams)	//need review

#define LWIP_GET_NETIF_PACKET_IN_sta() (sta_if.mib2_counters.ifinoctets)
#define LWIP_GET_NETIF_PACKET_OUT_sta() (sta_if.mib2_counters.ifoutoctets)

#define LWIP_GET_NETIF_PACKET_IN_ap() (ap_if.mib2_counters.ifinoctets)
#define LWIP_GET_NETIF_PACKET_OUT_ap() (ap_if.mib2_counters.ifoutoctets)

extern void metric_update( networkMetrics_t *pMetric );
extern void metric_update_pkt_byte_only( networkMetrics_t *pMetric );
extern void metric_clean( networkMetrics_t *pMetric );
extern void metric_reset( networkMetrics_t *pMetric );
extern void metric_display( networkMetrics_t *pMetric );



// should put in demos\include\iot_config_common.h
#define IotMetrics_Malloc pvPortMalloc              // do we need support static memory?
#define IotMetrics_Free vPortFree


#endif //__METRICS_H__
