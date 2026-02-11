add_early_maps(void)
{
	int i, ret;

	for (i = 0; i < early_ioapic_map_size; ++i) {
		ret = add_special_device(IVHD_SPECIAL_IOAPIC,
					 early_ioapic_map[i].id,
					 &early_ioapic_map[i].devid,
					 early_ioapic_map[i].cmd_line);
		if (ret)
			return ret;
	}

	for (i = 0; i < early_hpet_map_size; ++i) {
		ret = add_special_device(IVHD_SPECIAL_HPET,
					 early_hpet_map[i].id,
					 &early_hpet_map[i].devid,
					 early_hpet_map[i].cmd_line);
		if (ret)
			return ret;
	}

	return 0;
}
