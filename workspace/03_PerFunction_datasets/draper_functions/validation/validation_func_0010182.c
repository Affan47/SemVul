csio_hw_flash_fw(struct csio_hw *hw, int *reset)
{
	int ret = -ECANCELED;
	const struct firmware *fw;
	struct fw_info *fw_info;
	struct fw_hdr *card_fw;
	struct pci_dev *pci_dev = hw->pdev;
	struct device *dev = &pci_dev->dev ;
	const u8 *fw_data = NULL;
	unsigned int fw_size = 0;


	fw_info = find_fw_info(CHELSIO_CHIP_VERSION(hw->chip_id));
	if (fw_info == NULL) {
		csio_err(hw,
			"unable to get firmware info for chip %d.\n",
			CHELSIO_CHIP_VERSION(hw->chip_id));
		return -EINVAL;
	}

	if (request_firmware(&fw, FW_FNAME_T5, dev) < 0) {
		csio_err(hw, "could not find firmware image %s, err: %d\n",
			 FW_FNAME_T5, ret);
	} else {
		fw_data = fw->data;
		fw_size = fw->size;
	}


	card_fw = kmalloc(sizeof(*card_fw), GFP_KERNEL);


	ret = csio_hw_prep_fw(hw, fw_info, fw_data, fw_size, card_fw,
			 hw->fw_state, reset);


	if (fw != NULL)
		release_firmware(fw);
	kfree(card_fw);
	return ret;
}
