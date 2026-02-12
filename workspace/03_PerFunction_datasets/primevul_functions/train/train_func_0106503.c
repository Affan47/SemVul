int set_thread_uses_vas(void)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		return -EINVAL;

	current->thread.used_vas = 1;


	asm volatile(PPC_CP_ABORT);

#endif
	return 0;
}
