mwl8k_request_firmware(struct mwl8k_priv *priv, char *fw_image,
				  bool nowait)
{
	struct mwl8k_device_info *di = priv->device_info;
	int rc;

	if (di->helper_image != NULL) {
		if (nowait)
			rc = mwl8k_request_fw(priv, di->helper_image,
					      &priv->fw_helper, true);
		else
			rc = mwl8k_request_fw(priv, di->helper_image,
					      &priv->fw_helper, false);
		if (rc)
			printk(KERN_ERR "%s: Error requesting helper fw %s\n",
			       pci_name(priv->pdev), di->helper_image);

		if (rc || nowait)
			return rc;
	}

	if (nowait) {


		priv->fw_state = FW_STATE_LOADING_PREF;
		rc = mwl8k_request_fw(priv, fw_image,
				      &priv->fw_ucode,
				      true);
	} else
		rc = mwl8k_request_fw(priv, fw_image,
				      &priv->fw_ucode, false);
	if (rc) {
		printk(KERN_ERR "%s: Error requesting firmware file %s\n",
		       pci_name(priv->pdev), fw_image);
		mwl8k_release_fw(&priv->fw_helper);
		return rc;
	}

	return 0;
}
