supported_platform(struct s3_info_platform *nicid,
			      struct srec_data *srec, int dl_mode)
{
	int i;

	if (dl_mode == MODE_GENESIS &&
	    (skip_pda_read ||
	     (ignore_incompatible_interface &&
	      srec->component.component == HFA384X_COMP_ID_PRI))) {

		return 1;
	}

	for (i = 0; i < srec->platform_count; i++) {
		struct s3_info_platform *p = &srec->platforms[i];

		if (p->platform == nicid->platform &&
		    p->major == nicid->major &&
		    p->minor == nicid->minor &&
		    p->variant == nicid->variant)
			return 1;
	}


	if (dl_mode == MODE_NON_VOLATILE)
		return 0;

	for (i = 0; i < srec->platform_count; i++) {
		struct s3_info_platform *p = &srec->platforms[i];


		if (nicid->platform == 0x8008 && nicid->major == 1 &&
		    nicid->minor == 0 && nicid->variant == 1 &&
		    p->platform == 0x8008 && p->major == 1 &&
		    p->minor == 0 && p->variant == 0) {
			printf("Exact NICID was not found from the list of "
			       "supported platforms, but an\nalternative that "
			       "has been reported to work was found.\n");
			return 1;
		}
	}

	return 0;
}
