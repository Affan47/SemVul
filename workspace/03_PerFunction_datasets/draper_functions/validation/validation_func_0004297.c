ips_isinit_copperhead_memio(ips_ha_t * ha)
{
	uint8_t isr = 0;
	uint8_t scpr;

	METHOD_TRACE("ips_is_init_copperhead_memio", 1);

	isr = readb(ha->mem_ptr + IPS_REG_HISR);
	scpr = readb(ha->mem_ptr + IPS_REG_SCPR);

	if (((isr & IPS_BIT_EI) == 0) && ((scpr & IPS_BIT_EBM) == 0))
		return (0);
	else
		return (1);
}
