static void disable_cpuid(void)
{
	preempt_disable();
	if (!test_and_set_thread_flag(TIF_NOCPUID)) {


		set_cpuid_faulting(true);
	}
	preempt_enable();
}
