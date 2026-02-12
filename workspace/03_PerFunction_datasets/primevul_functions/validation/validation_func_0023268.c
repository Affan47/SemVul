static void tcg_log_global_after_sync(MemoryListener *listener)
{
    CPUAddressSpace *cpuas;


    if (replay_mode == REPLAY_MODE_NONE) {


        cpuas = container_of(listener, CPUAddressSpace, tcg_as_listener);
        run_on_cpu(cpuas->cpu, do_nothing, RUN_ON_CPU_NULL);
    }
}
