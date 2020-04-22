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
#define CHANMUX_CHANNEL_UNUSED_0        0
#define CHANMUX_CHANNEL_UNUSED_1        1
#define CHANMUX_CHANNEL_UNUSED_2        2
#define CHANMUX_CHANNEL_UNUSED_3        3
#define CHANMUX_CHANNEL_NIC_1_CTRL      4
#define CHANMUX_CHANNEL_NIC_1_DATA      5
#define CHANMUX_CHANNEL_UNUSED_6        6
#define CHANMUX_CHANNEL_UNUSED_7        7
#define CHANMUX_CHANNEL_UNUSED_8        8
#define CHANMUX_NUM_CHANNELS            9

#define SENDER_NIC_1                    101

//-----------------------------------------------------------------------------
// Network Stack
//-----------------------------------------------------------------------------
#define ETH_1_ADDR                  "10.0.0.10"
#define ETH_1_GATEWAY_ADDR          "10.0.0.1"
#define ETH_1_SUBNET_MASK           "255.255.255.0"