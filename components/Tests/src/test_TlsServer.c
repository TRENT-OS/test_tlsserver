/*
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "lib_macros/Test.h"
#include "TestConfig.h"

#include "OS_Tls.h"

#include "TlsServer.h"

#include <camkes.h>
#include <string.h>

static const if_TlsServer_t tlsServer =
    IF_TLSSERVER_ASSIGN(
        tlsServer_rpc);
static const OS_Tls_Config_t remoteCfg =
{
    .mode = OS_Tls_MODE_CLIENT,
    .rpc = IF_OS_TLS_ASSIGN(
        tlsServer_rpc,
        tlsServer_port)
};

// Private functions -----------------------------------------------------------

static void
test_TlsServer_connect_pos(
    void)
{
    TEST_START();

    /*
     * Establish a connection to the known TLS server and also perform a
     * complete handshake.
     *
     * NOTE: We DO NOT disconnect, as that is part of a follow-up test..
     */
    TEST_SUCCESS(TlsServer_connect(&tlsServer, TLS_HOST_IP, TLS_HOST_PORT));

    TEST_FINISH();
}

static void
test_TlsServer_connect_neg(
    void)
{
    TEST_START();

    /*
     * TODO: Once the NW layer is able to deal with connection failures we should
     *       add some test cases for that as well. These tests here just test a
     *       very basic parameter check in the TlsServer.
     */

    // Invalid IP
    TEST_INVAL_PARAM(TlsServer_connect(&tlsServer, "", TLS_HOST_PORT));

    // Invalid port
    TEST_INVAL_PARAM(TlsServer_connect(&tlsServer, TLS_HOST_IP, 0));

    TEST_FINISH();
}

static void
test_TlsServer_do_tls(
    void)
{
    const char request[] = "HELLOOOOOO?!";
    unsigned char buffer[1024];
    size_t len = sizeof(request);
    OS_Tls_Handle_t hTls;

    TEST_START();

    TEST_SUCCESS(OS_Tls_init(&hTls, &remoteCfg));
    TEST_SUCCESS(OS_Tls_handshake(hTls));

    TEST_SUCCESS(OS_Tls_write(hTls, request, &len));
    TEST_TRUE(len == sizeof(request));

    len = sizeof(request);
    memset(buffer, 0, sizeof(buffer));
    TEST_SUCCESS(OS_Tls_read(hTls, buffer, &len));
    TEST_TRUE(len == sizeof(request));
    TEST_TRUE(!memcmp(buffer, request, len));

    TEST_SUCCESS(OS_Tls_free(hTls));

    TEST_FINISH();
}

static void
test_TlsServer_disconnect_pos(
    void)
{
    TEST_START();

    // We come here after the successful execution of connect_pos(), so the socket
    // is connected and we should be able to disconnect.
    TEST_SUCCESS(TlsServer_disconnect(&tlsServer));

    TEST_FINISH();
}

static void
test_TlsServer_disconnect_neg(
    void)
{
    TEST_START();

    // Now the socket should be disconnected, so trying it again should fail.
    TEST_INVAL_STATE(TlsServer_disconnect(&tlsServer));

    TEST_FINISH();
}

// Public functions ------------------------------------------------------------

int run()
{
    Debug_LOG_INFO("Starting test of TlsServer");

    test_TlsServer_connect_neg();
    test_TlsServer_connect_pos();

    test_TlsServer_do_tls();

    test_TlsServer_disconnect_pos();
    test_TlsServer_disconnect_neg();

    Debug_LOG_INFO("All tests successfully completed.");

    return 0;
}
