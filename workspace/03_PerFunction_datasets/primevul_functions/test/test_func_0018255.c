void iwl_pcie_alloc_fw_monitor(struct iwl_trans *trans, u8 max_power)
{
	if (!max_power) {

		max_power = 26;
	} else {
		max_power += 11;
	}

	if (WARN(max_power > 26,
		 "External buffer size for monitor is too big %d, check the FW TLV\n",
		 max_power))
		return;


	if (trans->dbg.num_blocks)
		return;

	iwl_pcie_alloc_fw_monitor_block(trans, max_power, 11);
}
