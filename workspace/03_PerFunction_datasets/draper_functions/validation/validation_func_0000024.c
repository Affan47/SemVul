lcl_get_xstr_offset(int index, int res)
{
	if (res == GR_640) {
		return Xstr_table[index].offset_x;
	} else {
		return Xstr_table[index].offset_x_hi;
	}
}
