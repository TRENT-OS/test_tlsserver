/*
 *  Ticker
 *
 *  Copyright (C) 2019, Hensoldt Cyber GmbH
 *
 */

#include "LibDebug/Debug.h"
#include <camkes.h>

//------------------------------------------------------------------------------
int run(void)
{
    Debug_LOG_INFO("ticker running");

    // set up a tick every second
    int ret = timeServer_rpc_periodic(0, NS_IN_S);
    if (0 != ret)
    {
        Debug_LOG_ERROR("timeServer_rpc_periodic() failed, code %d", ret);
        return -1;
    }

    for(;;)
    {
        timeServer_notify_wait();

        // send a tick to the network stack
        e_timeout_nwstacktick_emit();
    }
}
