static void enable_TSC(void)
{
	preempt_disable();
	if (test_and_clear_thread_flag(TIF_NOTSC))


		cr4_clear_bits(X86_CR4_TSD);
	preempt_enable();
}
