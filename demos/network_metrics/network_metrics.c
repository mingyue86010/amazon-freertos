/* Standard includes. */
#include <stdint.h>
/* Lwip includes. */
#include "lwip/arch.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h" 				// #define LOCK_TCPIP_CORE()     sys_mutex_lock(&lock_tcpip_core)
#include "lwip/ip_addr.h" 				//ip_addr_t, ipaddr_ntoa, ip_addr_copy
#include "lwip/tcp.h"					// struct tcp_pcb
#include "lwip/priv/tcp_priv.h" 		//tcp_listen_pcbs_t
/* Platform layer includes. */
#include "platform/iot_threads.h"
/* Demo logging include. */
#include "iot_demo_logging.h"
/* Interface includes. */
#include "network_metrics.h"

#if ( FREERTOS_LWIP_METRICS_ENABLE == 1 )

extern struct tcp_pcb *tcp_active_pcbs; /* List of all TCP PCBs that are in a state in which they accept or send data. */
extern union tcp_listen_pcbs_t tcp_listen_pcbs; /* List of all TCP PCBs in LISTEN state */


LwipMetricStatus_t lwipGetOpenTcpPorts( uint16_t * pOutPortsArray,
                                            uint32_t portsArrayLength,
                                            uint32_t * pOutNumOpenPorts )
{
	LwipMetricStatus_t status = LwipMetricSuccess;
	struct tcp_pcb *pCurrPcb = tcp_listen_pcbs.listen_pcbs;
	uint16_t pcbCnt = 0;
	
	if( ( ( pOutPortsArray != NULL ) && ( portsArrayLength == 0 ) ) ||
    ( pOutNumOpenPorts == NULL ) )
    {
		IotLogError( ( "Invalid parameters. pLwipPcbsList: %p, pOutPortsArray: %p,"
                    " portsArrayLength: %u, pOutNumOpenPorts: %p.",
                    pOutPortsArray,
                    portsArrayLength,
                    pOutNumOpenPorts ) );
        status = LwipMetricBadParameter;
    }

	if ( status == LwipMetricSuccess )
	{
		LOCK_TCPIP_CORE();
		while ( pCurrPcb )
		{
			/*  write the ports into pOutPortsArray if not NULL */
			if ( ( pOutPortsArray != NULL ) && ( pcbCnt < portsArrayLength ))
			{	
				pOutPortsArray[ pcbCnt ] = pCurrPcb->local_port;			
			}

			++pcbCnt;
			pCurrPcb = pCurrPcb->next;
		}
		UNLOCK_TCPIP_CORE();
	}

	if( ( pOutPortsArray != NULL ) && ( pcbCnt > portsArrayLength ) )
	{
		//warning
	}

    if( status == LwipMetricSuccess )
    {
        *pOutNumOpenPorts = pcbCnt;
    }
	
	return status;

}


LwipMetricStatus_t lwipGetEstablishedConnections( Connection_t * pOutConnectionsArray,
												  uint32_t connectionsArrayLength, 
												  uint32_t * pOutNumEstablishedConnections  )
{
	LwipMetricStatus_t status = LwipMetricSuccess;
	struct tcp_pcb *pCurrPcb = tcp_active_pcbs;
	uint16_t pcbCnt = 0;
	Connection_t * pEstablishedConnection;

	if( ( ( pOutConnectionsArray != NULL ) && ( connectionsArrayLength == 0 ) ) ||
    ( pOutNumEstablishedConnections == NULL ) )
    {
		IotLogError( ( "Invalid parameters. pLwipPcbsList: %p, pOutConnectionsArray: %p,"
                    " connectionsArrayLength: %u, pOutNumEstablishedConnections: %p.",
                    pOutConnectionsArray,
                    connectionsArrayLength,
                    pOutNumEstablishedConnections ) );
        status = LwipMetricBadParameter;
    }

	if ( status == LwipMetricSuccess )
	{
		LOCK_TCPIP_CORE();
		while ( pCurrPcb )
		{
			/*  write the ports into pOutConnectionsArray if not NULL */
			if ( ( pOutConnectionsArray != NULL ) && ( pcbCnt < connectionsArrayLength ))
			{
				/* The output array member to fill. */
				pEstablishedConnection = &( pOutConnectionsArray[ pcbCnt ] );

				ip_addr_copy(pEstablishedConnection->remoteIp, pCurrPcb->remote_ip);	// network byte order
				ip_addr_copy(pEstablishedConnection->localIp, pCurrPcb->local_ip);		// network byte order
				pEstablishedConnection->localPort = pCurrPcb->local_port;; 				// host byte order 
				// For listen connection, this is invalid. 
				// Use tcp_listen_pcbs.pcbs instead of tcp_listen_pcbs.tcp_pcb_listen, 
				// so that it can share the code with remote connections.
				pEstablishedConnection->remotePort = pCurrPcb->remote_port;				
			}

			++pcbCnt;
			pCurrPcb = pCurrPcb->next;
		}
		UNLOCK_TCPIP_CORE();
	}

	if( ( pOutConnectionsArray != NULL ) && ( pcbCnt > connectionsArrayLength ) )
	{
		IotLogWarn( "The connectionsArrayLength is not long engough to hold the" );
	}

    if( status == LwipMetricSuccess )
    {
        *pOutNumEstablishedConnections = pcbCnt;
    }
	
	return status;
}


LwipMetricStatus_t lwipGetNetworkStats( NetworkStats_t * pOutNetworkStats ) 
{
	LwipMetricStatus_t status = LwipMetricSuccess;

    if( pOutNetworkStats == NULL )
    {
        IotLogError( ( "Invalid parameters. pOutNetworkStats: %p", pOutNetworkStats ) );
        status = LwipMetricBadParameter;
    }

	if ( status ==  LwipMetricSuccess )
	{
		LOCK_TCPIP_CORE();
		pOutNetworkStats->bytesReceived = LWIP_GET_NETIF_PACKET_IN_sta();
		pOutNetworkStats->bytesSent = LWIP_GET_NETIF_PACKET_OUT_sta();
		pOutNetworkStats->packetsReceived = LWIP_GET_TCP_PACKET_IN();
		pOutNetworkStats->packetsSent = LWIP_GET_TCP_PACKET_OUT();
		UNLOCK_TCPIP_CORE();
	}
	
	return status;
}


void metric_update( networkMetrics_t *pMetric ) {
	LOCK_TCPIP_CORE();
	pMetric->pktsIn = LWIP_GET_TCP_PACKET_IN();
    pMetric->pktsOut = LWIP_GET_TCP_PACKET_OUT();
    pMetric->bytesIn = LWIP_GET_NETIF_PACKET_IN_sta();
    pMetric->bytesOut = LWIP_GET_NETIF_PACKET_OUT_sta();
	pMetric->numOfActiveConnections = lwipPcbTriverse( tcp_active_pcbs, &_networkMetrics.remoteConnectionList );
	pMetric->numOfListenConnections = lwipPcbTriverse( tcp_listen_pcbs.pcbs, &_networkMetrics.listenConnectionList ); //tcp_listen_pcbs.tcp_pcb_listen
	UNLOCK_TCPIP_CORE();
}

#endif //FREERTOS_LWIP_METRICS_ENABLE
