of_unittest_destroy_tracked_overlays(void)
{
	int id, ret, defers;

	if (overlay_first_id < 0)
		return;


	do {
		defers = 0;

		for (id = MAX_UNITTEST_OVERLAYS - 1; id >= 0; id--) {
			if (!(overlay_id_bits[BIT_WORD(id)] & BIT_MASK(id)))
				continue;

			ret = of_overlay_destroy(id + overlay_first_id);
			if (ret != 0) {
				defers++;
				pr_warn("%s: overlay destroy failed for #%d\n",
					__func__, id + overlay_first_id);
				continue;
			}

			overlay_id_bits[BIT_WORD(id)] &= ~BIT_MASK(id);
		}
	} while (defers > 0);
}
