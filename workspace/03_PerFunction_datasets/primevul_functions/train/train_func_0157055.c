static void vendor_disable_error_reporting(void)
{


	if (boot_cpu_data.x86_vendor == X86_VENDOR_INTEL ||
	    boot_cpu_data.x86_vendor == X86_VENDOR_AMD)
		return;

	mce_disable_error_reporting();
}
