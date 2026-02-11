pcipcwd_check_temperature_support(void)
{
	if (inb_p(pcipcwd_private.io_addr) != 0xF0)
		pcipcwd_private.supports_temp = 1;
}
