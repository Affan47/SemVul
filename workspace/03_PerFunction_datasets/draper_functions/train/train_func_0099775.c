delRow(row_type row)
{
	if (nrows() == 1)
		return;

	cells_type::iterator it = cells_.begin() + row * ncols();
	cells_.erase(it, it + ncols());

	vector<CellInfo>::iterator jt = cellinfo_.begin() + row * ncols();
	cellinfo_.erase(jt, jt + ncols());

	rowinfo_.erase(rowinfo_.begin() + row);
}
