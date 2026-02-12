static inline void copy_kernel_to_fpregs(union fpregs_state *fpstate)
{


	if (unlikely(static_cpu_has_bug(X86_BUG_FXSAVE_LEAK))) {
		asm volatile(
			"fnclex\n\t"
			"emms\n\t"
			"fildl %P[addr]"
			: : [addr] "m" (fpstate));
	}

	__copy_kernel_to_fpregs(fpstate, -1);
}
