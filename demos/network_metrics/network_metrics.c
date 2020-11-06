/* Interface include. */
#include "network_metrics.h"

/* Lwip includes. */
#include "lwipopts.h"
#include "lwip/ip_addr.h"
#include "lwip/arch.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "lwip/ip_addr.h"
#include "lwip/tcp.h"
#include "lwip/priv/tcp_priv.h"

/* Demo logging include. */
#include "iot_demo_logging.h" /* GA - Why don't we use the new logging framework? */

#if !defined( LWIP_TCPIP_CORE_LOCKING_INPUT ) || ( LWIP_TCPIP_CORE_LOCKING_INPUT == 0 )
    #error "The network metric will not be supported if LWIP_TCPIP_CORE_LOCKING_INPUT is disabled."
#endif

/* Extern variables from LWIP. */
extern struct netif sta_if, ap_if;

#define LWIP_GET_PACKET_IN()           ( lwip_stats.mib2.ipinreceives )
#define LWIP_GET_PACKET_OUT()          ( lwip_stats.mib2.ipoutrequests )

#define LWIP_GET_BYTES_IN()            ( sta_if.mib2_counters.ifinoctets )
#define LWIP_GET_BYTES_OUT()           ( sta_if.mib2_counters.ifoutoctets )

/* Defined in the LWIP code. */
extern struct tcp_pcb * tcp_active_pcbs;        /* List of all TCP PCBs that are in a state in which they accept or send data. */
extern union tcp_listen_pcbs_t tcp_listen_pcbs; /* List of all TCP PCBs in LISTEN state */

/**
 * @brief Get a list of the listening TCP ports.
 *
 * This function finds the listening TCP ports by traversing LWIP TCP PCBs list that
 * in listen state. The header of the list is "tcp_listen_pcbs.listen_pcbs struture".
 * It can be called with @p pOutTcpPortsArray NULL to get the number of the open TCP ports.
 *
 * @param[in] pOutTcpPortsArray The array to write the open TCP ports into. This
 * can be NULL, if only the number of open ports is needed.
 * @param[in] tcpPortsArrayLength Length of the pOutTcpPortsArray, if it is not
 * NULL.
 * @param[out] pOutNumTcpOpenPorts Number of the open TCP ports.
 *
 * @return #LwipMetricSuccess if open TCP ports are successfully obtained;
 * #LwipMetricBadParameter if invalid parameters are passed;
 */
MetricStatus_t GetOpenTcpPorts( uint16_t * pOutTcpPortsArray,
                                uint32_t tcpPortsArrayLength,
                                uint32_t * pOutNumTcpOpenPorts )
{
    MetricStatus_t status = MetricSuccess;
    struct tcp_pcb_listen * pCurrPcb = tcp_listen_pcbs.listen_pcbs;
    uint16_t pcbCnt = 0;

    if( ( ( pOutTcpPortsArray != NULL ) && ( tcpPortsArrayLength == 0 ) ) ||
        ( pOutNumTcpOpenPorts == NULL ) )
    {
        IotLogError( "Invalid parameters. pOutTcpPortsArray: 0x%08x,"
                        "portsArrayLength: %u, pOutNumTcpOpenPorts: 0x%08x.",
                        pOutTcpPortsArray,
                        portsArrayLength,
                        pOutNumTcpOpenPorts );
        status = MetricBadParameter;
    }

    if( status == MetricSuccess )
    {
        LOCK_TCPIP_CORE();

        while( pCurrPcb )
        {
            /*  write the ports into pOutTcpPortsArray if not NULL. */
            if( ( pOutTcpPortsArray != NULL ) && ( pcbCnt < tcpPortsArrayLength ) )
            {
                pOutTcpPortsArray[ pcbCnt ] = pCurrPcb->local_port;
            }

            ++pcbCnt;
            pCurrPcb = pCurrPcb->next;
        }

        UNLOCK_TCPIP_CORE();
    }

    if( ( pOutTcpPortsArray != NULL ) && ( pcbCnt > tcpPortsArrayLength ) )
    {
        IotLogWarn( "The portsArrayLength is not long engough to store all the listening ports" );
    }

    if( status == MetricSuccess )
    {
        *pOutNumTcpOpenPorts = pcbCnt;
    }

    return status;
}
/*-----------------------------------------------------------*/

/**
 * @brief Get a list of established connections.
 *
 * This function finds the established connections by traversing LWIP TCP active PCBs list.
 * The header of LWIP TCP active PCBs list is "tcp_active_pcbs".
 * It can be called with @p pOutConnectionsArray NULL to get the number of
 * established connections.
 *
 * @param[in] pOutConnectionsArray The array to write the established connections
 * into. This can be NULL, if only the number of established connections is
 * needed.
 * @param[in] connectionsArrayLength Length of the pOutConnectionsArray, if it
 * is not NULL.
 * @param[out] pOutNumEstablishedConnections Number of the established connections.
 *
 * @return #LwipMetricSuccess if open TCP ports are successfully obtained;
 * #LwipMetricBadParameter if invalid parameters are passed;
 */
MetricStatus_t GetEstablishedConnections( Connection_t * pOutConnectionsArray,
                                          uint32_t connectionsArrayLength,
                                          uint32_t * pOutNumEstablishedConnections )
{
    MetricStatus_t status = MetricSuccess;
    struct tcp_pcb * pCurrPcb = tcp_active_pcbs;
    uint16_t pcbCnt = 0;
    Connection_t * pEstablishedConnection;

    if( ( ( pOutConnectionsArray != NULL ) && ( connectionsArrayLength == 0 ) ) ||
        ( pOutNumEstablishedConnections == NULL ) )
    {
        IotLogError( "Invalid parameters. pOutConnectionsArray: 0x%08x,"
                        " connectionsArrayLength: %u, pOutNumEstablishedConnections: 0x%08x.",
                        pOutConnectionsArray,
                        connectionsArrayLength,
                        pOutNumEstablishedConnections );
        status = MetricBadParameter;
    }

    if( status == MetricSuccess )
    {
        LOCK_TCPIP_CORE();

        while( pCurrPcb )
        {
            /*  write the ports into pOutConnectionsArray if not NULL */
            if( ( pOutConnectionsArray != NULL ) && ( pcbCnt < connectionsArrayLength ) )
            {
                /* The output array member to fill. */
                pEstablishedConnection = &( pOutConnectionsArray[ pcbCnt ] );

                ip_addr_copy( pEstablishedConnection->remoteIp, pCurrPcb->remote_ip ); /* network byte order */
                ip_addr_copy( pEstablishedConnection->localIp, pCurrPcb->local_ip );   /* network byte order */
                pEstablishedConnection->localPort = pCurrPcb->local_port;              /* host byte order */
                pEstablishedConnection->remotePort = pCurrPcb->remote_port;            /* host byte order */
            }

            ++pcbCnt;
            pCurrPcb = pCurrPcb->next;
        }

        UNLOCK_TCPIP_CORE();
    }

    if( ( pOutConnectionsArray != NULL ) && ( pcbCnt > connectionsArrayLength ) )
    {
        IotLogWarn( "The connectionsArrayLength is not long enough to store all the established connections" );
    }

    if( status == MetricSuccess )
    {
        *pOutNumEstablishedConnections = pcbCnt;
    }

    return status;
}
/*-----------------------------------------------------------*/

/**
 * @brief Get network stats.
 *
 * This function finds the network stats by reading MIB-II structure.
 *
 * @param[out] pOutNetworkStats The network stats.
 *
 * @return #LwipMetricSuccess if the network stats are successfully obtained;
 * #LwipMetricBadParameter if invalid parameters are passed;
 */
MetricStatus_t GetNetworkStats( NetworkStats_t * pOutNetworkStats )
{
    MetricStatus_t status = MetricSuccess;

    if( pOutNetworkStats == NULL )
    {
        IotLogError( "Invalid parameters. pOutNetworkStats: 0x%08x", pOutNetworkStats );
        status = MetricBadParameter;
    }

    if( status == MetricSuccess )
    {
        LOCK_TCPIP_CORE();
        pOutNetworkStats->bytesReceived = LWIP_GET_BYTES_IN();
        pOutNetworkStats->bytesSent = LWIP_GET_BYTES_OUT();
        pOutNetworkStats->packetsReceived = LWIP_GET_PACKET_IN();
        pOutNetworkStats->packetsSent = LWIP_GET_PACKET_OUT();
        UNLOCK_TCPIP_CORE();
    }

    return status;
}
/*-----------------------------------------------------------*/
