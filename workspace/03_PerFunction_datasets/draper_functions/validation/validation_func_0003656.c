hwm_conv_can(struct s_smc *smc, char *data, int len)
{
	int i ;

	SK_UNUSED(smc) ;

	for (i = len; i ; i--, data++)
		*data = bitrev8(*data);
}
