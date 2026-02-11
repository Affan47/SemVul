fdisk_reset_device_properties(struct fdisk_context *cxt)
{
	int rc;

	if (!cxt)
		return -EINVAL;

	DBG(CXT, ul_debugobj(cxt, "*** reseting device properties"));

	fdisk_zeroize_device_properties(cxt);
	fdisk_discover_topology(cxt);
	fdisk_discover_geometry(cxt);

	rc = fdisk_read_firstsector(cxt);
	if (rc)
		return rc;

	fdisk_apply_user_device_properties(cxt);
	return 0;
}
