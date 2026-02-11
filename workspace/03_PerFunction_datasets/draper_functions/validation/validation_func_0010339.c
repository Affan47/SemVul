Line_Attr_to_tmpfile(LineAttrKind kind, int value)
{
	LineAttrKind tk = kind;
	LineEnds tv = value;

	if (record_off)
		return;

	if (kind == LineAttrEnd)
		CurrentLineEnd = value;

	if (fwrite(&tk, sizeof(tk), 1, td) != 1) {
		PError("Line_Attr_to_tmpfile - kind");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}

	if (fwrite(&tv, sizeof(tv), 1, td) != 1) {
		PError("Line_Attr_to_tmpfile - value");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}

	return;
}
