adjacent_point(__isl_keep isl_vec *sample, int pos, int up)
{
	if (up)
		isl_int_add_ui(sample->el[1 + pos], sample->el[1 + pos], 1);
	else
		isl_int_sub_ui(sample->el[1 + pos], sample->el[1 + pos], 1);
}
