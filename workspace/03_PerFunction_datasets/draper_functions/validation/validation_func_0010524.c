qla2x00_thermal_temp_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	uint16_t temp = 0;

	if (qla2x00_reset_active(vha)) {
		ql_log(ql_log_warn, vha, 0x70dc, "ISP reset active.\n");
		goto done;
	}

	if (vha->hw->flags.eeh_busy) {
		ql_log(ql_log_warn, vha, 0x70dd, "PCI EEH busy.\n");
		goto done;
	}

	if (qla2x00_get_thermal_temp(vha, &temp) == QLA_SUCCESS)
		return scnprintf(buf, PAGE_SIZE, "%d\n", temp);

done:
	return scnprintf(buf, PAGE_SIZE, "\n");
}
