qla4_82xx_set_idc_ver(struct scsi_qla_host *ha)
{
	int idc_ver;
	uint32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
	if (drv_active == (1 << (ha->func_num * 4))) {
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION,
				    QLA82XX_IDC_VERSION);
		ql4_printk(KERN_INFO, ha,
			   "%s: IDC version updated to %d\n", __func__,
			   QLA82XX_IDC_VERSION);
	} else {
		idc_ver = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION);
		if (QLA82XX_IDC_VERSION != idc_ver) {
			ql4_printk(KERN_INFO, ha,
				   "%s: qla4xxx driver IDC version %d is not compatible with IDC version %d of other drivers!\n",
				   __func__, QLA82XX_IDC_VERSION, idc_ver);
		}
	}
}
