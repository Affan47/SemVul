efx_siena_sriov_usrev(struct efx_nic *efx, bool enabled)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	EFX_POPULATE_OWORD_2(reg,
			     FRF_CZ_USREV_DIS, enabled ? 0 : 1,
			     FRF_CZ_DFLT_EVQ, nic_data->vfdi_channel->channel);
	efx_writeo(efx, &reg, FR_CZ_USR_EV_CFG);
}
