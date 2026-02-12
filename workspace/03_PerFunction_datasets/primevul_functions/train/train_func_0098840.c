static void enable_cpuid(void)
{
	preempt_disable();
	if (test_and_clear_thread_flag(TIF_NOCPUID)) {


		set_cpuid_faulting(false);
	}
	preempt_enable();
}
