static void __cpuinit kvm_setup_secondary_clock(void)
{


	WARN_ON(kvm_register_clock("secondary cpu clock"));

	setup_secondary_APIC_clock();
}
