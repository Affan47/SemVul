wr_item(const object_type *o_ptr)
{
	size_t i;

	wr_u16b(0xffff);
	wr_byte(ITEM_VERSION);

	wr_s16b(o_ptr->k_idx);


	wr_byte(o_ptr->iy);
	wr_byte(o_ptr->ix);

	wr_byte(o_ptr->tval);
	wr_byte(o_ptr->sval);
	wr_s16b(o_ptr->pval);

	wr_byte(0);

	wr_byte(o_ptr->number);
	wr_s16b(o_ptr->weight);

	wr_byte(o_ptr->name1);
	wr_byte(o_ptr->name2);

	wr_s16b(o_ptr->timeout);

	wr_s16b(o_ptr->to_h);
	wr_s16b(o_ptr->to_d);
	wr_s16b(o_ptr->to_a);
	wr_s16b(o_ptr->ac);
	wr_byte(o_ptr->dd);
	wr_byte(o_ptr->ds);

	wr_u16b(o_ptr->ident);

	wr_byte(o_ptr->marked);

	wr_byte(o_ptr->origin);
	wr_byte(o_ptr->origin_depth);
	wr_u16b(o_ptr->origin_xtra);


	for (i = 0; i < 12 && i < OF_SIZE; i++)
		wr_byte(o_ptr->flags[i]);
	if (i < 12) pad_bytes(12 - i);


	for (i = 0; i < 12 && i < OF_SIZE; i++)
		wr_byte(o_ptr->known_flags[i]);
	if (i < 12) pad_bytes(12 - i);


	wr_s16b(o_ptr->held_m_idx);


	if (o_ptr->note)
	{
		wr_string(quark_str(o_ptr->note));
	}
	else
	{
		wr_string("");
	}
}
