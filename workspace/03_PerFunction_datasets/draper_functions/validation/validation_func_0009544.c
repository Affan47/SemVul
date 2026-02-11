bnx2i_identify_device(struct bnx2i_hba *hba, struct cnic_dev *dev)
{
	hba->cnic_dev_type = 0;
	if (test_bit(CNIC_F_BNX2_CLASS, &dev->flags)) {
		if (hba->pci_did == PCI_DEVICE_ID_NX2_5706 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5706S) {
			set_bit(BNX2I_NX2_DEV_5706, &hba->cnic_dev_type);
		} else if (hba->pci_did == PCI_DEVICE_ID_NX2_5708 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5708S) {
			set_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type);
		} else if (hba->pci_did == PCI_DEVICE_ID_NX2_5709 ||
		    hba->pci_did == PCI_DEVICE_ID_NX2_5709S) {
			set_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type);
			hba->mail_queue_access = BNX2I_MQ_BIN_MODE;
		}
	} else if (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) {
		set_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type);
	} else {
		printk(KERN_ALERT "bnx2i: unknown device, 0x%x\n",
				  hba->pci_did);
	}
}
