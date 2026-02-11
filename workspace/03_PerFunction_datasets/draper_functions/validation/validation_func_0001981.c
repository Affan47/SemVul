efx_siena_sriov_bufs(struct efx_nic *efx, unsigned offset,
				 u64 *addr, unsigned count)
{
	efx_qword_t buf;
	unsigned pos;

	for (pos = 0; pos < count; ++pos) {
		EFX_POPULATE_QWORD_3(buf,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF,
				     addr ? addr[pos] >> 12 : 0,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		efx_sram_writeq(efx, efx->membase + FR_BZ_BUF_FULL_TBL,
				&buf, offset + pos);
	}
}
