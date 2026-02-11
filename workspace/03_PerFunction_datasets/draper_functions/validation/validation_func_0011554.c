evaluate(const nomme &first, const nomme &second) const
    {
	const inode *first_i = get_inode(&first);
	infinint first_date = first_i != NULL ? first_i->get_last_modif() : 0;

	return first_i == NULL || first_date >= x_date || tools_is_equal_with_hourshift(x_hourshift, first_date, x_date);
    }
