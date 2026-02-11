falcon_ack_status_intr(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	if ((efx_nic_rev(efx) != EFX_REV_FALCON_B0) || LOOPBACK_INTERNAL(efx))
		return;


	if (!efx->link_state.up)
		return;


	if (nic_data->xmac_poll_required)
		return;

	efx_reado(efx, &reg, FR_AB_XM_MGT_INT_MSK);
}
