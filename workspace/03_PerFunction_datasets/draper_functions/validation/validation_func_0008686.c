IoBlock_justCode(IoBlock *self)
{
	UArray *ba = UArray_new();

	if (DATA(self)->scope)
	{
		UArray_appendCString_(ba, "block(");
	}
	else
	{
		UArray_appendCString_(ba, "method(");
	}

	LIST_FOREACH(DATA(self)->argNames, i, argName,
		UArray_append_(ba, IoSeq_rawUArray((IoSymbol *)argName));
		UArray_appendCString_(ba, ", ");
	);

	{
		UArray *d = IoMessage_description(DATA(self)->message);
		UArray_append_(ba, d);
		UArray_free(d);
	}

	UArray_appendCString_(ba, ")");
	return ba;
}
