/*
 * Copyright (C) 2019-2020, Hensoldt Cyber GmbH
 *
 * Library configurations
 *
 */

#pragma once


//-----------------------------------------------------------------------------
// Debug
//-----------------------------------------------------------------------------
#if !defined(NDEBUG)
#   define Debug_Config_STANDARD_ASSERT
#   define Debug_Config_ASSERT_SELF_PTR
#else
#   define Debug_Config_DISABLE_ASSERT
#   define Debug_Config_NO_ASSERT_SELF_PTR
#endif

#define Debug_Config_LOG_LEVEL              Debug_LOG_LEVEL_INFO
#define Debug_Config_INCLUDE_LEVEL_IN_MSG
#define Debug_Config_LOG_WITH_FILE_LINE

//-----------------------------------------------------------------------------
// TlsServer Clients
//-----------------------------------------------------------------------------
#define TLSSERVER_CLIENT_ID_1      0


//-----------------------------------------------------------------------------
// TimeServer Clients
//-----------------------------------------------------------------------------
#define TIMESERVER_TK_ID      1
#define TIMESERVER_NS_ID      2


//-----------------------------------------------------------------------------
// Memory
//-----------------------------------------------------------------------------
#define Memory_Config_USE_STDLIB_ALLOC


//-----------------------------------------------------------------------------
// Logs
//-----------------------------------------------------------------------------
#define Logs_Config_LOG_STRING_SIZE         128
#define Logs_Config_INCLUDE_LEVEL_IN_MSG    1
#define Logs_Config_SYSLOG_LEVEL            Log_ERROR


//-----------------------------------------------------------------------------
// ChanMUX
//-----------------------------------------------------------------------------

#define CHANMUX_CHANNEL_NIC_CTRL      4
#define CHANMUX_CHANNEL_NIC_DATA      5


//-----------------------------------------------------------------------------
// ChanMUX clients
//-----------------------------------------------------------------------------

#define CHANMUX_ID_NIC        101


//-----------------------------------------------------------------------------
// Network Stack
//-----------------------------------------------------------------------------
#define ETH_1_ADDR                  "10.0.0.10"
#define ETH_1_GATEWAY_ADDR          "10.0.0.1"
#define ETH_1_SUBNET_MASK           "255.255.255.0"


//-----------------------------------------------------------------------------
// Network Driver
//-----------------------------------------------------------------------------

#define NIC_DRIVER_RINGBUFFER_NUMBER_ELEMENTS 16
#define NIC_DRIVER_RINGBUFFER_SIZE                                             \
    (NIC_DRIVER_RINGBUFFER_NUMBER_ELEMENTS * 4096)
