DtsGetHWFeatures(uint32_t *pciids)
{
	int drvHandle = -1;
	BC_IOCTL_DATA pIo;
	int rc;

	memset(&pIo, 0, sizeof(BC_IOCTL_DATA));

	drvHandle =open(CRYSTALHD_API_DEV_NAME, O_RDWR);
	if(drvHandle < 0)
	{
		DebugLog_Trace(LDIL_ERR,"DtsGetHWFeatures: Create File Failed\n");
		return BC_STS_ERROR;
	}

	pIo.u.pciCfg.Offset = 0;
	pIo.u.pciCfg.Size = 4;

	rc = ioctl(drvHandle, BCM_IOC_RD_PCI_CFG, &pIo);
	if(rc < 0){
		DebugLog_Trace(LDIL_ERR,"ioctl to get HW features failed\n");
		close(drvHandle);
		return BC_STS_ERROR;
	}

	if(pIo.RetSts == BC_STS_SUCCESS) {
		*pciids = pIo.u.pciCfg.pci_cfg_space[0] |
					(pIo.u.pciCfg.pci_cfg_space[1] << 8) |
					(pIo.u.pciCfg.pci_cfg_space[2] << 16) |
					(pIo.u.pciCfg.pci_cfg_space[3] << 24);

		close(drvHandle);
		return BC_STS_SUCCESS;
	}
	else {
		DebugLog_Trace(LDIL_ERR, "error in getting pciids\n");
		close(drvHandle);
		return BC_STS_ERROR;
	}
}
