lpfc_sli_prep_dev_for_perm_failure(struct lpfc_hba *phba)
{
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2711 PCI channel permanent disable for failure\n");

	lpfc_scsi_dev_block(phba);


	lpfc_stop_hba_timers(phba);


	lpfc_sli_flush_fcp_rings(phba);
}
