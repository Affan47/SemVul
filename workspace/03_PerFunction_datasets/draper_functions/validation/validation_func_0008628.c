get_row_descriptors(struct uwb_rsv_alloc_info *ai)
{
	unsigned char *bm = ai->bm;
	struct uwb_rsv_row_info *ri = &ai->ri;
	int col, mas;

	ri->free_rows = 16;
	for (mas = 0; mas < UWB_MAS_PER_ZONE; mas ++) {
		ri->avail[mas] = 1;
		for (col = 1; col < UWB_NUM_ZONES; col++) {
			if (bm[col * UWB_NUM_ZONES + mas] == UWB_RSV_MAS_NOT_AVAIL) {
				ri->free_rows--;
				ri->avail[mas]=0;
				break;
			}
		}
	}
}
