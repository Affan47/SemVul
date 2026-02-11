qlcnic_check_idc_ver(struct qlcnic_adapter *adapter)
{
	u32 val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_IDC_VER);

	if (val != QLCNIC_DRV_IDC_VER) {
		dev_warn(&adapter->pdev->dev, "IDC Version mismatch, driver's"
			" idc ver = %x; reqd = %x\n", QLCNIC_DRV_IDC_VER, val);
	}

	return 0;
}
