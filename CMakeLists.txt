#
# Test TLS Server
#
# Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(
    config/SystemConfig.h
    CONFIG_PROJECT_NAME system_config)

#-------------------------------------------------------------------------------
project(test_tlsserver C)

include("plat/${PLATFORM}/plat_nic.cmake")

TlsServer_DeclareCAmkESComponent(
    TlsServer
    LIBS
        os_crypto
        os_socket_client
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
        lib_macros
        os_crypto
        os_tls
        TlsServer_client
)

DeclareCAmkESComponent(
    NwStack
    SOURCES
        components/NwStack/src/network_stack.c
    C_FLAGS
        -Wall
        -Werror
        -DCFG_ETH_ADDR=ETH_1_ADDR
        -DCFG_ETH_GATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DCFG_ETH_SUBNET_MASK=ETH_1_SUBNET_MASK
    LIBS
        system_config
        os_core_api
        lib_debug
        os_network_lib
        TimeServer_client
)

DeclareCAmkESComponent(
    Ticker
    SOURCES
        components/Ticker/Ticker.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        lib_debug
)

TimeServer_DeclareCAmkESComponent(
    TimeServer
)

EntropySource_DeclareCAmkESComponent(
    EntropySource
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
