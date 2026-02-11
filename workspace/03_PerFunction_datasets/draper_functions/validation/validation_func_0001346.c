_fill_device_data(struct thread_status *ts)
{
	struct dm_task *dmt;
	struct dm_info dmi;

	if (!ts->device.uuid)
		return 0;

	ts->device.name = NULL;
	ts->device.major = ts->device.minor = 0;

	dmt = dm_task_create(DM_DEVICE_INFO);
	if (!dmt)
		return 0;

	if (!dm_task_set_uuid(dmt, ts->device.uuid))
		goto fail;

	if (!dm_task_run(dmt))
		goto fail;

	ts->device.name = dm_strdup(dm_task_get_name(dmt));
	if (!ts->device.name)
		goto fail;

	if (!dm_task_get_info(dmt, &dmi))
		goto fail;

	ts->device.major = dmi.major;
	ts->device.minor = dmi.minor;

	dm_task_destroy(dmt);
	return 1;

      fail:
	dm_task_destroy(dmt);
	dm_free(ts->device.name);
	return 0;
}
