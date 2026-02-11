acpi_video_resume(struct notifier_block *nb,
				unsigned long val, void *ign)
{
	struct acpi_video_bus *video;
	struct acpi_video_device *video_device;
	int i;

	switch (val) {
	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
	case PM_RESTORE_PREPARE:
		return NOTIFY_DONE;
	}

	video = container_of(nb, struct acpi_video_bus, pm_nb);

	dev_info(&video->device->dev, "Restoring backlight state\n");

	for (i = 0; i < video->attached_count; i++) {
		video_device = video->attached_array[i].bind_info;
		if (video_device && video_device->brightness)
			acpi_video_device_lcd_set_level(video_device,
					video_device->brightness->curr);
	}

	return NOTIFY_OK;
}
