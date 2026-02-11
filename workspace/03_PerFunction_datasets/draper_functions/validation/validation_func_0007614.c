hns_dsaf_tbl_tcam_init(struct dsaf_device *dsaf_dev)
{
	u32 i;
	struct dsaf_tbl_tcam_data tcam_data[] = {{0, 0} };
	struct dsaf_tbl_tcam_ucast_cfg tcam_ucast[] = {{0, 0, 0, 0, 0} };


	for (i = 0; i < DSAF_TCAM_SUM; i++)
		hns_dsaf_tcam_uc_cfg(dsaf_dev, i, tcam_data, tcam_ucast);
}
