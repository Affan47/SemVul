asmlinkage long sys_getpgrp(void)
{

	return process_group(current);
}
