int check_line_hdr(void)
{
	int i, rc = FALSE;


	if (get_activity_nr(act, AO_SELECTED, COUNT_OUTPUTS) > 1)
		return TRUE;

	for (i = 0; i < NR_ACT; i++) {
		if (IS_SELECTED(act[i]->options)) {

			if (act[i]->bitmap) {
				if (count_bits(act[i]->bitmap->b_array,
					       BITMAP_SIZE(act[i]->bitmap->b_size)) > 1) {
					rc = TRUE;
				}
			}
			else if (act[i]->nr_ini > 1) {
				rc = TRUE;
			}

			break;
		}
	}

	return rc;
}
