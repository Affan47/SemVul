set_ioapic_sid(struct irte *irte, int apic)
{
	int i;
	u16 sid = 0;

	if (!irte)
		return -1;

	down_read(&dmar_global_lock);
	for (i = 0; i < MAX_IO_APICS; i++) {
		if (ir_ioapic[i].iommu && ir_ioapic[i].id == apic) {
			sid = (ir_ioapic[i].bus << 8) | ir_ioapic[i].devfn;
			break;
		}
	}
	up_read(&dmar_global_lock);

	if (sid == 0) {
		pr_warn("Failed to set source-id of IOAPIC (%d)\n", apic);
		return -1;
	}

	set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16, sid);

	return 0;
}
