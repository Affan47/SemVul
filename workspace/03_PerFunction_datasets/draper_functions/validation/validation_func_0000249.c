phram_param_call(const char *val, struct kernel_param *kp)
{
#ifdef MODULE
	return phram_setup(val);
#else


	if (phram_init_called)
		return phram_setup(val);


	if (strlen(val) >= sizeof(phram_paramline))
		return -ENOSPC;
	strcpy(phram_paramline, val);

	return 0;
#endif
}
