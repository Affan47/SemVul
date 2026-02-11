new_csubmatrix (header *hd, header *rows, header *cols,
	char *name)
{	if (nosubmref) return built_csmatrix(hd,rows,cols);
	return hnew_submatrix(hd,rows,cols,name,s_csubmatrix);
}
