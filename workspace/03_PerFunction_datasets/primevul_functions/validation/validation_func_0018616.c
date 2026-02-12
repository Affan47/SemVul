static __init int sev_hardware_setup(void)
{
	struct sev_user_data_status *status;
	int rc;


	max_sev_asid = cpuid_ecx(0x8000001F);

	if (!max_sev_asid)
		return 1;


	min_sev_asid = cpuid_edx(0x8000001F);


	sev_asid_bitmap = bitmap_zalloc(max_sev_asid, GFP_KERNEL);
	if (!sev_asid_bitmap)
		return 1;

	sev_reclaim_asid_bitmap = bitmap_zalloc(max_sev_asid, GFP_KERNEL);
	if (!sev_reclaim_asid_bitmap)
		return 1;

	status = kmalloc(sizeof(*status), GFP_KERNEL);
	if (!status)
		return 1;


	rc = sev_platform_status(status, NULL);
	if (rc)
		goto err;

	pr_info("SEV supported\n");

err:
	kfree(status);
	return rc;
}
