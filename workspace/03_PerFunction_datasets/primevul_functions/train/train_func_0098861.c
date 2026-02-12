void disable_TSC(void)
{
	preempt_disable();
	if (!test_and_set_thread_flag(TIF_NOTSC))


		cr4_set_bits(X86_CR4_TSD);
	preempt_enable();
}
