setThreadAffinity (nat n, nat m)
{
    nat nproc;
    cpu_set_t cs;
    nat i;

    nproc = getNumberOfProcessors();
    CPU_ZERO(&cs);
    for (i = n; i < nproc; i+=m) {
        CPU_SET(i, &cs);
    }
    sched_setaffinity(0, sizeof(cpu_set_t), &cs);
}
