static void tcg_commit(MemoryListener *listener)
{
    CPUState *cpu;


    CPU_FOREACH(cpu) {


        if (cpu->tcg_as_listener != listener) {
            continue;
        }
        cpu_reload_memory_map(cpu);
    }
}
