/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://aws.amazon.com/freertos
 * https://www.FreeRTOS.org
 */

/**
 * @file metrics_collector.c
 *
 * @brief Functions used by the defender demo to collect metrics on the
 * device's open ports and sockets. FreeRTOS+TCP tcp_netstat utility
 * is used to collect this metrics.
 */

/* Standard includes. */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOS_IP.h"

/* FreeRTOS+TCP tcp_netstat utility include. */
#include "tcp_netstat.h"

/* Demo config. */
#include "defender_demo_config.h"

/* Interface include. */
#include "metrics_collector.h"
/*-----------------------------------------------------------*/

MetricsCollectorStatus_t GetNetworkStats( NetworkStats_t * pOutNetworkStats )
{
    MetricsCollectorStatus_t status = MetricsCollectorSuccess;

    MetricsType_t metrics = { 0 };
    BaseType_t metricsStatus = 0;

    configASSERT( pOutNetworkStats != NULL );

    /* Start with everything as zero. */
    memset( pOutNetworkStats, 0, sizeof( NetworkStats_t ) );

    /* Get metrics from FreeRTOS+TCP tcp_netstat utility. */
    metricsStatus = vGetMetrics( &metrics );

    if( metricsStatus != 0 )
    {
        LogError( ( "Failed to acquire metrics from FreeRTOS+TCP tcp_netstat utility. Status: %d.",
                    ( int ) metricsStatus ) );
        status = MetricsCollectorCollectionFailed;
    }

    /* Fill our response with values gotten from FreeRTOS+TCP. */
    if( status == MetricsCollectorSuccess )
    {
        LogDebug( ( "Network stats read. Bytes received: %u, packets received: %u, "
                    "bytes sent: %u, packets sent: %u.",
                    ( unsigned int ) metrics.xInput.uxByteCount,
                    ( unsigned int ) metrics.xInput.uxPacketCount,
                    ( unsigned int ) metrics.XOutput.uxByteCount,
                    ( unsigned int ) metrics.XOutput.uxPacketCount ) );

        pOutNetworkStats->bytesReceived = metrics.xInput.uxByteCount;
        pOutNetworkStats->packetsReceived = metrics.xInput.uxPacketCount;
        pOutNetworkStats->bytesSent = metrics.XOutput.uxByteCount;
        pOutNetworkStats->packetsSent = metrics.XOutput.uxPacketCount;
    }

    return status;
}
/*-----------------------------------------------------------*/

MetricsCollectorStatus_t GetOpenTcpPorts( uint16_t * pOutTcpPortsArray,
                                          uint32_t tcpPortsArrayLength,
                                          uint32_t * pOutNumTcpOpenPorts )
{
    MetricsCollectorStatus_t status = MetricsCollectorSuccess;

    MetricsType_t metrics = { 0 };
    BaseType_t metricsStatus = 0;
    uint32_t copyAmount = 0UL;

    /* pOutTcpPortsArray can be NULL. */
    configASSERT( pOutNumTcpOpenPorts != NULL );

    /* Get metrics from FreeRTOS+TCP tcp_netstat utility. */
    metricsStatus = vGetMetrics( &metrics );

    if( metricsStatus != 0 )
    {
        LogError( ( "Failed to acquire metrics from FreeRTOS+TCP tcp_netstat utility. Status: %d.",
                    ( int ) metricsStatus ) );
        status = MetricsCollectorCollectionFailed;
    }

    if( status == MetricsCollectorSuccess )
    {
        /* Fill the output array with as many TCP ports as will fit in the
         * given array. */
        if( pOutTcpPortsArray != NULL )
        {
            copyAmount = metrics.xTCPPortList.uxCount;

            /* Limit the copied ports to what can fit in the output array. */
            if( tcpPortsArrayLength < metrics.xTCPPortList.uxCount )
            {
                LogWarn( ( "Ports returned truncated due to insufficient buffer size." ) );
                copyAmount = tcpPortsArrayLength;
            }

            memcpy( pOutTcpPortsArray, &metrics.xTCPPortList.usTCPPortList, copyAmount * sizeof( uint16_t ) );

            /* Return the number of elements copied to the array. */
            *pOutNumTcpOpenPorts = copyAmount;
        }
        else
        {
            /* Return the total number of open ports. */
            *pOutNumTcpOpenPorts = metrics.xTCPPortList.uxCount;
        }
    }

    return MetricsCollectorSuccess;
}
/*-----------------------------------------------------------*/

MetricsCollectorStatus_t GetOpenUdpPorts( uint16_t * pOutUdpPortsArray,
                                          uint32_t udpPortsArrayLength,
                                          uint32_t * pOutNumUdpOpenPorts )
{
    MetricsCollectorStatus_t status = MetricsCollectorSuccess;

    MetricsType_t metrics = { 0 };
    BaseType_t metricsStatus = 0;
    uint32_t copyAmount = 0UL;

    /* pOutUdpPortsArray can be NULL. */
    configASSERT( pOutNumUdpOpenPorts != NULL );

    /* Get metrics from FreeRTOS+TCP tcp_netstat utility. */
    metricsStatus = vGetMetrics( &metrics );

    if( metricsStatus != 0 )
    {
        LogError( ( "Failed to acquire metrics from FreeRTOS+TCP tcp_netstat utility. Status: %d.",
                    ( int ) metricsStatus ) );
        status = MetricsCollectorCollectionFailed;
    }

    if( status == MetricsCollectorSuccess )
    {
        /* Fill the output array with as many UDP ports as will fit in the
         * given array. */
        if( pOutUdpPortsArray != NULL )
        {
            copyAmount = metrics.xUDPPortList.uxCount;

            /* Limit the copied ports to what can fit in the output array. */
            if( udpPortsArrayLength < metrics.xUDPPortList.uxCount )
            {
                LogWarn( ( "Ports returned truncated due to insufficient buffer size." ) );
                copyAmount = udpPortsArrayLength;
            }

            memcpy( pOutUdpPortsArray, &metrics.xUDPPortList.usUDPPortList, copyAmount * sizeof( uint16_t ) );

            /* Return the number of elements copied to the array. */
            *pOutNumUdpOpenPorts = copyAmount;
        }
        else
        {
            /* Return the total number of open ports. */
             *pOutNumUdpOpenPorts = metrics.xUDPPortList.uxCount;
        }
    }

    return MetricsCollectorSuccess;
}

/*-----------------------------------------------------------*/

MetricsCollectorStatus_t GetEstablishedConnections( Connection_t * pOutConnectionsArray,
                                                    uint32_t connectionsArrayLength,
                                                    uint32_t * pOutNumEstablishedConnections )
{
    MetricsCollectorStatus_t status = MetricsCollectorSuccess;

    MetricsType_t metrics = { 0 };
    BaseType_t metricsStatus = 0;
    uint32_t copyAmount = 0UL;
    uint32_t localIp = 0UL;
    uint32_t i;

    /* pOutConnectionsArray can be NULL. */
    configASSERT( pOutNumEstablishedConnections != NULL );

    /* Get metrics from FreeRTOS+TCP tcp_netstat utility. */
    metricsStatus = vGetMetrics( &metrics );

    if( metricsStatus != 0 )
    {
        LogError( ( "Failed to acquire metrics from FreeRTOS+TCP tcp_netstat utility. Status: %d.",
                    ( int ) metricsStatus ) );
        status = MetricsCollectorCollectionFailed;
    }

    if( status == MetricsCollectorSuccess )
    {
        /* Fill the output array with as many TCP socket infos as will fit in
         * the given array. */
        if( pOutConnectionsArray != NULL )
        {
            copyAmount = metrics.xTCPSocketList.uxCount;

            /* Get local IP as the tcp_netstat utility does not give it. */
            localIp = FreeRTOS_GetIPAddress();

            /* Limit the outputted connections to what can fit in the output array. */
            if( connectionsArrayLength < metrics.xTCPSocketList.uxCount )
            {
                LogWarn( ( "Ports returned truncated due to insufficient buffer size." ) );
                copyAmount = connectionsArrayLength;
            }

            for( i = 0; i < copyAmount; i++ )
            {
                pOutConnectionsArray[ i ].localIp = localIp;
                pOutConnectionsArray[ i ].localPort =
                    metrics.xTCPSocketList.xTCPList[ i ].usLocalPort;
                pOutConnectionsArray[ i ].remoteIp =
                    metrics.xTCPSocketList.xTCPList[ i ].ulRemoteIP;
                pOutConnectionsArray[ i ].remotePort =
                    metrics.xTCPSocketList.xTCPList[ i ].usRemotePort;
            }

            /* Return the number of elements copied to the array. */
            *pOutNumEstablishedConnections = copyAmount;
        }
        else
        {
            /* Return the total number of established connections. */
            *pOutNumEstablishedConnections = metrics.xTCPSocketList.uxCount;
        }
    }

    return status;
}
/*-----------------------------------------------------------*/
