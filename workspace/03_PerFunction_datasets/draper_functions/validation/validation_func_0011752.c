mvumi_proc_msg(struct mvumi_hba *mhba,
					struct mvumi_hotplug_event *param)
{
	u16 size = param->size;
	const unsigned long *ar_bitmap;
	const unsigned long *re_bitmap;
	int index;

	if (mhba->fw_flag & MVUMI_FW_ATTACH) {
		index = -1;
		ar_bitmap = (const unsigned long *) param->bitmap;
		re_bitmap = (const unsigned long *) &param->bitmap[size >> 3];

		mutex_lock(&mhba->sas_discovery_mutex);
		do {
			index = find_next_zero_bit(ar_bitmap, size, index + 1);
			if (index >= size)
				break;
			mvumi_handle_hotplug(mhba, index, DEVICE_ONLINE);
		} while (1);

		index = -1;
		do {
			index = find_next_zero_bit(re_bitmap, size, index + 1);
			if (index >= size)
				break;
			mvumi_handle_hotplug(mhba, index, DEVICE_OFFLINE);
		} while (1);
		mutex_unlock(&mhba->sas_discovery_mutex);
	}
}
