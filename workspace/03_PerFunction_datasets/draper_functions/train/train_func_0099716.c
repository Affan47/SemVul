qla2300_pci_config(scsi_qla_host_t *vha)
{
	uint16_t	w;
	unsigned long   flags = 0;
	uint32_t	cnt;
	struct qla_hw_data *ha = vha->hw;
	struct device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_read_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);

	if (IS_QLA2322(ha) || IS_QLA6322(ha))
		w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_write_config_word(ha->pdev, PCI_COMMAND, w);


	if (IS_QLA2300(ha)) {
		spin_lock_irqsave(&ha->hardware_lock, flags);


		WRT_REG_WORD(&reg->hccr, HCCR_PAUSE_RISC);
		for (cnt = 0; cnt < 30000; cnt++) {
			if ((RD_REG_WORD(&reg->hccr) & HCCR_RISC_PAUSE) != 0)
				break;

			udelay(10);
		}


		WRT_REG_WORD(&reg->ctrl_status, 0x20);
		RD_REG_WORD(&reg->ctrl_status);


		ha->fb_rev = RD_FB_CMD_REG(ha, reg);

		if (ha->fb_rev == FPM_2300)
			pci_clear_mwi(ha->pdev);


		WRT_REG_WORD(&reg->ctrl_status, 0x0);
		RD_REG_WORD(&reg->ctrl_status);


		WRT_REG_WORD(&reg->hccr, HCCR_RELEASE_RISC);
		for (cnt = 0; cnt < 30000; cnt++) {
			if ((RD_REG_WORD(&reg->hccr) & HCCR_RISC_PAUSE) == 0)
				break;

			udelay(10);
		}

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	}

	pci_write_config_byte(ha->pdev, PCI_LATENCY_TIMER, 0x80);

	pci_disable_rom(ha->pdev);


	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->pci_attr = RD_REG_WORD(&reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	return QLA_SUCCESS;
}
