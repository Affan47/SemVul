static void xen_write_msr(unsigned int msr, unsigned low, unsigned high)
{


	xen_write_msr_safe(msr, low, high);
}
