wiz_test_kind(int tval)
{
	int py = p_ptr->py;
	int px = p_ptr->px;
	int sval;

	object_type object_type_body;
	object_type *i_ptr = &object_type_body;

	for (sval = 0; sval < 255; sval++)
	{
		int k_idx = lookup_kind(tval, sval);

		if (k_idx)
		{

			object_prep(i_ptr, k_idx, p_ptr->depth, RANDOMISE);


			apply_magic(i_ptr, p_ptr->depth, FALSE, FALSE, FALSE);


			i_ptr->origin = ORIGIN_CHEAT;
			i_ptr->origin_depth = p_ptr->depth;

			if (k_info[k_idx].tval == TV_GOLD)
				make_gold(i_ptr, p_ptr->depth, sval);


			drop_near(i_ptr, 0, py, px, TRUE);
		}
	}

	msg_print("Done.");
}
