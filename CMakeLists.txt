cmake_minimum_required(VERSION 3.7.2)

seos_set_config_file(config/SystemConfig.h)

seos_use_libs(
    SEOS_LIBS
    SEOS_CHANMUX
    SEOS_LIBS_LOGGER
    SEOS_NW_STACK
    SEOS_CRYPTO
    SEOS_CRYPTO_IMPL_MBEDTLS
    SEOS_NETWORK_DRIVER_TAP_PROXY
    SEOS_TLS_WITH_RPC_CLIENT
    SEOS_TLS_IMPL_MBEDTLS
)

# Set path to src, inc, camkes folders of TlsServer
SET(COMPONENTS_TLSSERVER_DIR "${SEOS_COMPONENTS_DIR}/TlsServer")

# Include TlsServer CMakeList
include("${COMPONENTS_TLSSERVER_DIR}/CMakeLists.txt")

DeclareCAmkESComponent(test_TlsServer
    INCLUDES
        config
        ${COMPONENTS_TLSSERVER_DIR}/inc
    SOURCES
        components/Tests/src/test_TlsServer.c
    C_FLAGS
        -Wall -Werror
    LIBS
        seos_core_api
        seos_libs
        seos_crypto
        seos_tls_with_rpc_client
)

DeclareCAmkESComponent(NwStack
    INCLUDES
        config
    SOURCES
        components/NwStack/src/network_stack.c
    C_FLAGS
        -Wall -Werror
        -DSEOS_NWSTACK_AS_CLIENT
        -DCFG_ETH_ADDR=ETH_1_ADDR
        -DCFG_ETH_GATEWAY_ADDR=ETH_1_GATEWAY_ADDR
        -DCFG_ETH_SUBNET_MASK=ETH_1_SUBNET_MASK
    LIBS
        seos_core_api
        seos_libs
        seos_nw_lib
)

DeclareCAmkESComponent(NwDriver
    SOURCES
        components/NwDriver/src/nic_driver.c
    C_FLAGS
        -Wall -Werror
        -DCFG_CHANMUX_CHANNEL_CRTL=CHANMUX_CHANNEL_NIC_1_CTRL
        -DCFG_CHANMUX_CHANNEL_DATA=CHANMUX_CHANNEL_NIC_1_DATA
    LIBS
        seos_core_api
        seos_libs
        seos_nw_driver_tap_proxy_lib
)

DeclareCAmkESComponent(ChanMux
    INCLUDES
        config
    SOURCES
        components/ChanMux/src/ChanMux.c
    C_FLAGS
        -Wall -Werror
    LIBS
        seos_core_api
        seos_libs
        chanmux_server
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

DeclareCAmkESRootserver(main.camkes)
GenerateCAmkESRootServer()
GenerateSimulateScript()
