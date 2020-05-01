cmake_minimum_required(VERSION 3.7.2)

seos_set_config_file(config/SystemConfig.h)

seos_use_libs(
    SEOS_LIBS
    SEOS_CHANMUX
    SEOS_LIBS_LOGGER
    SEOS_NW_STACK
    SEOS_CRYPTO
    SEOS_NETWORK_DRIVER_TAP_PROXY
    SEOS_TLS_WITH_RPC_CLIENT
)

project(system_config C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE config)


# Set path to src, inc, camkes folders of TlsServer
SET(COMPONENTS_TLSSERVER_DIR "${SEOS_COMPONENTS_DIR}/TlsServer")

# Include TlsServer CMakeList
include("${COMPONENTS_TLSSERVER_DIR}/CMakeLists.txt")

DeclareCAmkESComponent(test_TlsServer
    INCLUDES
        ${COMPONENTS_TLSSERVER_DIR}/inc
    SOURCES
        components/Tests/src/test_TlsServer.c
    C_FLAGS
        -Wall -Werror
    LIBS
        system_config
        seos_core_api
        seos_libs
        seos_crypto
        seos_tls_with_rpc_client
)

DeclareCAmkESComponent(NwStack
    SOURCES
        components/NwStack/src/network_stack.c
    C_FLAGS
        -Wall -Werror
        -DSEOS_NWSTACK_AS_CLIENT
        -DCFG_ETH_ADDR=ETH_1_ADDR
        -DCFG_ETH_GATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DCFG_ETH_SUBNET_MASK=ETH_1_SUBNET_MASK
    LIBS
        system_config
        seos_core_api
        seos_libs
        seos_nw_lib
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

DeclareCAmkESComponent(UartDrv
    SOURCES
        components/UART/src/UartDrv.c
        components/UART/src/qemu_uart.c
    C_FLAGS
        -Wall -Werror
    LIBS
        seos_libs
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
