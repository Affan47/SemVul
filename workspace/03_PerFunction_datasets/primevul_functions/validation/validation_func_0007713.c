static void task_struct_whitelist(unsigned long *offset, unsigned long *size)
{

	arch_thread_struct_whitelist(offset, size);


	if (unlikely(*size == 0))
		*offset = 0;
	else
		*offset += offsetof(struct task_struct, thread);
}
