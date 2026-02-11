select_generate_sel_table(select_t * sel)
{
	register cmph_uint8 * bits_table = (cmph_uint8 *)sel->bits_vec;
	register cmph_uint32 part_sum, old_part_sum;
	register cmph_uint32 vec_idx, one_idx, sel_table_idx;

	part_sum = vec_idx = one_idx = sel_table_idx = 0;

	for(;;)
	{

		if(one_idx >= sel->n)
			break;
		do
		{
			old_part_sum = part_sum;
			part_sum += rank_lookup_table[bits_table[vec_idx]];
			vec_idx++;
		} while (part_sum <= one_idx);

		sel->select_table[sel_table_idx] = select_lookup_table[bits_table[vec_idx - 1]][one_idx - old_part_sum] + ((vec_idx - 1) << 3);
		one_idx += STEP_SELECT_TABLE ;
		sel_table_idx++;
	};
}
