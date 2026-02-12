static void kvm_setup_secondary_clock(void)
{


	WARN_ON(kvm_register_clock("secondary cpu clock"));
}
