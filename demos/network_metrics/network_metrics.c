#include <stdint.h>
#include "lwip/arch.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h" 				// #define LOCK_TCPIP_CORE()     sys_mutex_lock(&lock_tcpip_core)
#include "lwip/ip_addr.h" 			//ip_addr_t, ipaddr_ntoa, ip_addr_copy
#include "lwip/tcp.h"						// struct tcp_pcb
#include "lwip/priv/tcp_priv.h" //tcp_listen_pcbs_t
#include "network_metrics.h"
/* Platform layer includes. */
#include "platform/iot_threads.h"
/* Demo logging include. */
#include "iot_demo_logging.h"

#if ( FREERTOS_LWIP_METRICS_ENABLE == 1 )

extern struct tcp_pcb *tcp_active_pcbs; /* List of all TCP PCBs that are in a state in which they accept or send data. */
extern union tcp_listen_pcbs_t tcp_listen_pcbs; /* List of all TCP PCBs in LISTEN state */

networkMetrics_t _networkMetrics = {
	.pktsIn = 0,
    .pktsOut = 0,
    .bytesIn = 0,
    .bytesOut = 0,
    .numOfActiveConnections = 0,
	.remoteConnectionList = NULL,
	.listenConnectionList = NULL
};

// Do we need a lock??? If using atomic would be better for pktsIn/Out and bytesIn/Out?
//static IotMutex_t _remoteConnectionListMutex;

//static void metricsTryGetLock( void ){
//}

//static void metricUnLock( void ){
//}


/* should be used with LOCK_TCPIP_CORE() */
static uint16_t lwip_pcb_triverse( struct tcp_pcb *lwip_tcp_pcbs_list, connections_t **pConnList ){
	//struct tcp_pcb *pCurrPcb = tcp_active_pcbs;
	struct tcp_pcb *pCurrPcb = lwip_tcp_pcbs_list;
	uint16_t pcbCnt = 0;
	connections_t *pConn = *pConnList, *pConnPre;

	while ( pCurrPcb ){
		/* Only malloc if the current list is not long enough, otherwise overwrite it */
		if ( !pConn ){
			pConn = IotMetrics_Malloc( sizeof( connections_t ) );
			memset( pConn, 0, sizeof( connections_t ) );
			if ( !*pConnList ){
				*pConnList = pConn;
			}
		}	

		++pcbCnt;
		
		ip_addr_copy(pConn->addr, pCurrPcb->remote_ip);
		// For listen connection, this is invalid. 
		// Use tcp_listen_pcbs.pcbs instead of tcp_listen_pcbs.tcp_pcb_listen, 
		// so that it can share the code with remote connections.
		pConn->port = pCurrPcb->remote_port;				
		
		pConnPre = pConn;
		pConn = pConn->next;
		pCurrPcb = pCurrPcb->next;
	}
	pConnPre->next = NULL;

	/* Free the extra aged remote connections records */
	while ( pConn ){
		pConnPre = pConn;
		pConn = pConn->next;
		IotMetrics_Free(pConnPre);
	} 

	return pcbCnt;
}


void metric_update( networkMetrics_t *pMetric ) {
	LOCK_TCPIP_CORE();
	pMetric->pktsIn = LWIP_GET_TCP_PACKET_IN();
    pMetric->pktsOut = LWIP_GET_TCP_PACKET_OUT();
    pMetric->bytesIn = LWIP_GET_NETIF_PACKET_IN_sta();
    pMetric->bytesOut = LWIP_GET_NETIF_PACKET_OUT_sta();
	pMetric->numOfActiveConnections = lwip_pcb_triverse( tcp_active_pcbs, &_networkMetrics.remoteConnectionList );
	pMetric->numOfListenConnections = lwip_pcb_triverse( tcp_listen_pcbs.pcbs, &_networkMetrics.listenConnectionList ); //tcp_listen_pcbs.tcp_pcb_listen
	UNLOCK_TCPIP_CORE();
}

void metric_update_pkt_byte_only( networkMetrics_t *pMetric ) {
	LOCK_TCPIP_CORE();
	pMetric->pktsIn = LWIP_GET_TCP_PACKET_IN();
    pMetric->pktsOut = LWIP_GET_TCP_PACKET_OUT();
    pMetric->bytesIn = LWIP_GET_NETIF_PACKET_IN_sta();
    pMetric->bytesOut = LWIP_GET_NETIF_PACKET_OUT_sta();
	UNLOCK_TCPIP_CORE();
}

void metric_clean_pcbs_list( connections_t *connList ) {
	connections_t *pConn, *pConnPre;
	pConn = connList;
	while (pConn){
		pConnPre = pConn;
		pConn = pConn->next;
		IotMetrics_Free(pConnPre);
	}
}

void metric_clean( networkMetrics_t *pMetric ) {
	metric_clean_pcbs_list( pMetric->remoteConnectionList );
	metric_clean_pcbs_list( pMetric->listenConnectionList );
	memset( pMetric, 0, sizeof( networkMetrics_t ) );
}

void metric_reset( networkMetrics_t *pMetric ) {
	metric_clean( pMetric );
	metric_update( pMetric );
}

// Debug
void metric_display( networkMetrics_t *pMetric ){
	connections_t *pConn;
	
	IotLogInfo( "packet-in: %d", pMetric->pktsIn );
	IotLogInfo( "packet-out: %d", pMetric->pktsOut );
	IotLogInfo( "bytes-in-sta: %d", pMetric->bytesIn );
	IotLogInfo( "bytes-out-sta: %d", pMetric->bytesOut );

	IotLogInfo( "#Remote Connections: %d", pMetric->numOfActiveConnections );
	IotLogInfo( "&remoteConnectionList: %d", (int) pMetric->remoteConnectionList );
	pConn = pMetric->remoteConnectionList;
	while (pConn){
		IotLogInfo( "Remote port: %d", pConn->port );
		IotLogInfo( "Remote IP Address: %s", ipaddr_ntoa(((const ip_addr_t *)&pConn->addr))); 
		pConn = pConn->next;
	}

	IotLogInfo( "#Listen Connections: %d", pMetric->numOfListenConnections );
	IotLogInfo( "&listenConnectionList: %d", (int) pMetric->listenConnectionList );
	pConn = pMetric->listenConnectionList;
	while (pConn){
		IotLogInfo( "Remote port: %d", pConn->port );
		IotLogInfo( "Remote IP Address: %s", ipaddr_ntoa(((const ip_addr_t *)&pConn->addr))); 
		pConn = pConn->next;
	}

}

#endif //FREERTOS_LWIP_METRICS_ENABLE
