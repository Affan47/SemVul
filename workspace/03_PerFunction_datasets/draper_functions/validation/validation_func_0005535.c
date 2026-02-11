pmu_msr_write(unsigned int msr, uint32_t low, uint32_t high, int *err)
{
	uint64_t val = ((uint64_t)high << 32) | low;

	if (boot_cpu_data.x86_vendor == X86_VENDOR_AMD) {
		if (is_amd_pmu_msr(msr)) {
			if (!xen_amd_pmu_emulate(msr, &val, 0))
				*err = native_write_msr_safe(msr, low, high);
			return true;
		}
	} else {
		int type, index;

		if (is_intel_pmu_msr(msr, &type, &index)) {
			if (!xen_intel_pmu_emulate(msr, &val, type, index, 0))
				*err = native_write_msr_safe(msr, low, high);
			return true;
		}
	}

	return false;
}
