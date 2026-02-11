IoMessage_locals_symbolArgAt_(IoMessage *self, IoObject *locals, int n)
{
	IoObject *v = IoMessage_locals_valueArgAt_(self, locals, n);

	if (!ISSEQ(v))
	{
		IoMessage_locals_numberArgAt_errorForType_(self, locals, n, "Sequence");
	}

	return IoSeq_rawAsSymbol(v);
}
