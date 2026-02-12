static inline int restore_fpu_checking(struct task_struct *tsk)
{


	if (unlikely(static_cpu_has(X86_FEATURE_FXSAVE_LEAK))) {
		asm volatile(
			"fnclex\n\t"
			"emms\n\t"
			"fildl %P[addr]"
			: : [addr] "m" (tsk->thread.fpu.has_fpu));
	}

	return fpu_restore_checking(&tsk->thread.fpu);
}
