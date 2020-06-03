cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(config/SystemConfig.h)

os_use_libs(
    OS_LIBS
    OS_CHANMUX
    OS_LIBS_LOGGER
    OS_CRYPTO
    OS_TLS_WITH_RPC_CLIENT
)

project(system_config C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE config)


DeclareCAmkESComponent_TlsServer(TlsServer
    LIBS
        seos_crypto
        os_network_api
)

DeclareCAmkESComponent(test_TlsServer
    SOURCES
        components/Tests/src/test_TlsServer.c
    C_FLAGS
        -Wall -Werror
    LIBS
        system_config
        seos_core_api
        seos_libs
        seos_crypto
        TlsServer_client
)

DeclareCAmkESComponent(NwStack
    SOURCES
        components/NwStack/src/network_stack.c
    C_FLAGS
        -Wall -Werror
        -DOS_NWSTACK_AS_CLIENT
        -DCFG_ETH_ADDR=ETH_1_ADDR
        -DCFG_ETH_GATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DCFG_ETH_SUBNET_MASK=ETH_1_SUBNET_MASK
    LIBS
        system_config
        seos_core_api
        seos_libs
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

DeclareCAmkESComponent(TimerClient
    SOURCES
        components/TimerClient/src/Timer_Client.c
    C_FLAGS
        -Wall -Werror
    LIBS
        seos_libs
)

DeclareCAmkESComponent(Timer
    SOURCES
        components/Timer/src/timer.c
    C_FLAGS
        -Wall -Werror
    LIBS
        seos_libs
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
