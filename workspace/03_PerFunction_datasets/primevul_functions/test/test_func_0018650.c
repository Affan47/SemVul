static void tcg_commit(MemoryListener *listener)
{
    CPUAddressSpace *cpuas;
    AddressSpaceDispatch *d;


    cpuas = container_of(listener, CPUAddressSpace, tcg_as_listener);
    cpu_reloading_memory_map();


    d = address_space_to_dispatch(cpuas->as);
    cpuas->memory_dispatch = d;
    tlb_flush(cpuas->cpu);
}
