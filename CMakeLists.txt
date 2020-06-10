#
# Test TLS Server
#
# Copyright (C) 2020, Hensoldt Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(config/SystemConfig.h)

#-------------------------------------------------------------------------------
project(system_config C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE config)


#-------------------------------------------------------------------------------
project(test_tlsserver C)

DeclareCAmkESComponent_TlsServer(
    TlsServer
    LIBS
        os_crypto
        os_network_api
)

DeclareCAmkESComponent(
    test_TlsServer
    SOURCES
        components/Tests/src/test_TlsServer.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        system_config
        os_core_api
        os_libs
        os_crypto
        TlsServer_client
)

DeclareCAmkESComponent(
    NwStack
    SOURCES
        components/NwStack/src/network_stack.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_NWSTACK_AS_CLIENT
        -DCFG_ETH_ADDR=ETH_1_ADDR
        -DCFG_ETH_GATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DCFG_ETH_SUBNET_MASK=ETH_1_SUBNET_MASK
    LIBS
        system_config
        os_core_api
        os_libs
        os_network_lib
)

DeclareCAmkESComponent_NIC_ChanMux(
    NwDriver
    CHANMUX_CHANNEL_NIC_CTRL
    CHANMUX_CHANNEL_NIC_DATA
)

DeclareCAmkESComponent_ChanMux(
    ChanMux
    components/ChanMux/ChanMux_config.c
    system_config
)

DeclareCAmkESComponent_UART(
    UART
)

DeclareCAmkESComponent(
    TimerClient
    SOURCES
        components/TimerClient/src/Timer_Client.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_libs
)

DeclareCAmkESComponent(
    Timer
    SOURCES
        components/Timer/src/timer.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_libs
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
