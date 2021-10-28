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
        lib_debug
        os_crypto
        os_socket_client
        os_tls
        TlsServer_client
)

NetworkStack_PicoTcp_DeclareCAmkESComponent(
    NetworkStack_PicoTcp
    C_FLAGS
        -DNetworkStack_PicoTcp_USE_HARDCODED_IPADDR
        -DDEV_ADDR=ETH_1_ADDR
        -DGATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DSUBNET_MASK=ETH_1_SUBNET_MASK
)

TimeServer_DeclareCAmkESComponent(
    TimeServer
)

EntropySource_DeclareCAmkESComponent(
    EntropySource
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
