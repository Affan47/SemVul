void stop_this_cpu(void *dummy)
{
	local_irq_disable();


	set_cpu_online(smp_processor_id(), false);
	disable_local_APIC();
	mcheck_cpu_clear(this_cpu_ptr(&cpu_info));


	if (boot_cpu_has(X86_FEATURE_SME))
		native_wbinvd();
	for (;;) {


		native_halt();
	}
}
