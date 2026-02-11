STORAGE_IsReady (uint8_t lun) {
	if (filerGetMSCState() <= FILER_STATE_MSC_EJECT) {
		STORAGE_Init(lun);
		return -1;
	} else if (filerGetMSCState() != FILER_STATE_MSC_ACTIVE || !SD_Initialized() || !SD_TransferComplete()) {
		return (-1);
	} else {
		return (0);
	}
}
