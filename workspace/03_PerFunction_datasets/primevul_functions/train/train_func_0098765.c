static void __init xen_pv_guest_late_init(void)
{
#ifndef CONFIG_SMP

	xen_setup_vcpu_info_placement();
#endif
}
