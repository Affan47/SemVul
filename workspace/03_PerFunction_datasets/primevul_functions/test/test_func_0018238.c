static bool iwl_trans_pcie_grab_nic_access(struct iwl_trans *trans,
					   unsigned long *flags)
{
	int ret;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_irqsave(&trans_pcie->reg_lock, *flags);

	if (trans_pcie->cmd_hold_nic_awake)
		goto out;


	__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
				 BIT(trans->trans_cfg->csr->flag_mac_access_req));
	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
		udelay(2);


	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   BIT(trans->trans_cfg->csr->flag_val_mac_access_en),
			   (BIT(trans->trans_cfg->csr->flag_mac_clock_ready) |
			    CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	if (unlikely(ret < 0)) {
		u32 cntrl = iwl_read32(trans, CSR_GP_CNTRL);

		WARN_ONCE(1,
			  "Timeout waiting for hardware access (CSR_GP_CNTRL 0x%08x)\n",
			  cntrl);

		iwl_trans_pcie_dump_regs(trans);

		if (iwlwifi_mod_params.remove_when_gone && cntrl == ~0U) {
			struct iwl_trans_pcie_removal *removal;

			if (test_bit(STATUS_TRANS_DEAD, &trans->status))
				goto err;

			IWL_ERR(trans, "Device gone - scheduling removal!\n");


			if (!try_module_get(THIS_MODULE)) {
				IWL_ERR(trans,
					"Module is being unloaded - abort\n");
				goto err;
			}

			removal = kzalloc(sizeof(*removal), GFP_ATOMIC);
			if (!removal) {
				module_put(THIS_MODULE);
				goto err;
			}


			set_bit(STATUS_TRANS_DEAD, &trans->status);

			removal->pdev = to_pci_dev(trans->dev);
			INIT_WORK(&removal->work, iwl_trans_pcie_removal_wk);
			pci_dev_get(removal->pdev);
			schedule_work(&removal->work);
		} else {
			iwl_write32(trans, CSR_RESET,
				    CSR_RESET_REG_FLAG_FORCE_NMI);
		}

err:
		spin_unlock_irqrestore(&trans_pcie->reg_lock, *flags);
		return false;
	}

out:


	__release(&trans_pcie->reg_lock);
	return true;
}
