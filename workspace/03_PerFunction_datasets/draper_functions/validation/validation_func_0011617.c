prt_equippy(int row, int col)
{
	int i;

	byte a;
	char c;

	object_type *o_ptr;


	if (use_bigtile) return;


	for (i = INVEN_WIELD; i < INVEN_TOTAL; i++)
	{

		o_ptr = &inventory[i];

		a = object_attr(o_ptr);
		c = object_char(o_ptr);


		if (!o_ptr->k_idx)
		{
			c = ' ';
			a = TERM_WHITE;
		}


		Term_putch(col + i - INVEN_WIELD, row, a, c);
	}
}
