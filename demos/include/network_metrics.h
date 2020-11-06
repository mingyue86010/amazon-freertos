#ifndef METRICS_COLLECTOR_H_
#define METRICS_COLLECTOR_H_

/* Standard includes. */
#include <stdint.h>

/**
 * @brief Return codes from metrics collector APIs.
 */
typedef enum
{
    MetricSuccess = 0,
    MetricBadParameter
} MetricStatus_t;

/**
 * @brief Represents a network connection.
 */
typedef struct Connection
{
    uint32_t localIp;
    uint32_t remoteIp;
    uint16_t localPort;
    uint16_t remotePort;
} Connection_t;

/**
 * @brief Represents network stats.
 */
typedef struct NetworkStats
{
    uint32_t bytesReceived;   /**< Number of bytes received. */
    uint32_t bytesSent;       /**< Number of bytes sent. */
    uint32_t packetsReceived; /**< Number of packets (ethernet frames) received. */
    uint32_t packetsSent;     /**< Number of packets (ethernet frames) sent. */
} NetworkStats_t;

MetricStatus_t GetNetworkStats( NetworkStats_t * pOutNetworkStats );

MetricStatus_t GetEstablishedConnections( Connection_t * pOutConnectionsArray,
                                          uint32_t connectionsArrayLength,
                                          uint32_t * pOutNumEstablishedConnections );

MetricStatus_t GetOpenTcpPorts( uint16_t * pOutTcpPortsArray,
                                uint32_t tcpPortsArrayLength,
                                uint32_t * pOutNumOpenTcpPorts );

MetricStatus_t GetOpenUdpPorts( uint16_t * pOutUdpPortsArray,
                                uint32_t udpPortsArrayLength,
                                uint32_t * pOutNumOpenTcpPorts );

#endif /* METRICS_COLLECTOR_H_ */
