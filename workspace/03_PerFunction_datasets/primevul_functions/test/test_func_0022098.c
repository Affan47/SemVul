void syscall_init(void)
{


	wrmsrl(MSR_STAR,  ((u64)__USER32_CS)<<48  | ((u64)__KERNEL_CS)<<32);
	wrmsrl(MSR_LSTAR, system_call);

#ifdef CONFIG_IA32_EMULATION
	syscall32_cpu_init ();
#endif


	wrmsrl(MSR_SYSCALL_MASK, EF_TF|EF_DF|EF_IE|0x3000);
}
