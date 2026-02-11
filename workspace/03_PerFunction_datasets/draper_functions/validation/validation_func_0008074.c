moreCapabilities (nat from USED_IF_THREADS, nat to USED_IF_THREADS)
{
#if defined(THREADED_RTS)
    nat i;
    Capability *old_capabilities = capabilities;

    if (to == 1) {


        capabilities = &MainCapability;
    } else {
        capabilities = stgMallocBytes(to * sizeof(Capability),
                                      "moreCapabilities");

        if (from > 0) {
            memcpy(capabilities, old_capabilities, from * sizeof(Capability));
        }
    }

    for (i = from; i < to; i++) {
	initCapability(&capabilities[i], i);
    }

    last_free_capability = &capabilities[0];

    debugTrace(DEBUG_sched, "allocated %d more capabilities", to - from);


    if (from > 1) {
        return old_capabilities;
    } else {
        return NULL;
    }
#else
    return NULL;
#endif
}
