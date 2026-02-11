xpc_get_partition_rsvd_page_pa_uv(void *buf, u64 *cookie, unsigned long *rp_pa,
				  size_t *len)
{
	s64 status;
	enum xp_retval ret;

#if defined CONFIG_X86_64
	status = uv_bios_reserved_page_pa((u64)buf, cookie, (u64 *)rp_pa,
					  (u64 *)len);
	if (status == BIOS_STATUS_SUCCESS)
		ret = xpSuccess;
	else if (status == BIOS_STATUS_MORE_PASSES)
		ret = xpNeedMoreInfo;
	else
		ret = xpBiosError;

#elif defined CONFIG_IA64_GENERIC || defined CONFIG_IA64_SGI_UV
	status = sn_partition_reserved_page_pa((u64)buf, cookie, rp_pa, len);
	if (status == SALRET_OK)
		ret = xpSuccess;
	else if (status == SALRET_MORE_PASSES)
		ret = xpNeedMoreInfo;
	else
		ret = xpSalError;

#else
	#error not a supported configuration
#endif

	return ret;
}
