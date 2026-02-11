efx_mcdi_port_probe(struct efx_nic *efx)
{
	int rc;


	efx->phy_op = &efx_mcdi_phy_ops;


	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	efx->mdio.mdio_read = efx_mcdi_mdio_read;
	efx->mdio.mdio_write = efx_mcdi_mdio_write;


	rc = efx->phy_op->probe(efx);
	if (rc != 0)
		return rc;


	rc = efx_nic_alloc_buffer(efx, &efx->stats_buffer,
				  MC_CMD_MAC_NSTATS * sizeof(u64), GFP_KERNEL);
	if (rc)
		return rc;
	netif_dbg(efx, probe, efx->net_dev,
		  "stats buffer at %llx (virt %p phys %llx)\n",
		  (u64)efx->stats_buffer.dma_addr,
		  efx->stats_buffer.addr,
		  (u64)virt_to_phys(efx->stats_buffer.addr));

	efx_mcdi_mac_stats(efx, EFX_STATS_DISABLE, 1);

	return 0;
}
