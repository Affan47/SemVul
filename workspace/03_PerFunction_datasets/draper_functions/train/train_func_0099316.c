cpunum_resume(int cpunum, int reason)
{
	VERIFY_CPUNUM_VOID(cpunum_resume);
	LOG(("cpunum_resume (CPU=%d, r=%X)\n", cpunum, reason));


	cpu[cpunum].nextsuspend &= ~reason;
	if (cpu_getexecutingcpu() >= 0)
		activecpu_abort_timeslice();
}
