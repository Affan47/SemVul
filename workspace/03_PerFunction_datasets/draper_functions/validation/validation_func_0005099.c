sort_compare_sets (GnmSortData const *data, int indexa, int indexb,
		   gboolean default_locale)
{
	GnmCell *ca, *cb;
	int clause = 0;

	while (clause < data->num_clause) {
		int result = 0;
		int offset = data->clauses[clause].offset;

		if (data->top) {
			ca = sheet_cell_get (data->sheet,
					     data->range->start.col + offset,
					     data->range->start.row + indexa);
			cb = sheet_cell_get (data->sheet,
					     data->range->start.col + offset,
					     data->range->start.row + indexb);
		} else {
			ca = sheet_cell_get (data->sheet,
					     data->range->start.col + indexa,
					     data->range->start.row + offset);
			cb = sheet_cell_get (data->sheet,
					     data->range->start.col + indexb,
					     data->range->start.row + offset);
		}

		result = sort_compare_cells (ca, cb, &(data->clauses[clause]),
					     default_locale);
		if (result) {
			return result;
		}
		clause++;
	}


	return indexa - indexb;
}
