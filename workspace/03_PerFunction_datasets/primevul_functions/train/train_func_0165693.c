static void vmx_disable_intercept_for_msr(struct page *msr_bitmap, u32 msr)
{
	void *va;

	if (!cpu_has_vmx_msr_bitmap())
		return;


	va = kmap(msr_bitmap);
	if (msr <= 0x1fff) {
		__clear_bit(msr, va + 0x000);
		__clear_bit(msr, va + 0x800);
	} else if ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) {
		msr &= 0x1fff;
		__clear_bit(msr, va + 0x400);
		__clear_bit(msr, va + 0xc00);
	}
	kunmap(msr_bitmap);
}
