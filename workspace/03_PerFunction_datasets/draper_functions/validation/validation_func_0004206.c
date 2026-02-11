do_text_output_multiline(TupOutputState *tstate, char *text)
{
	Datum		values[1];
	bool		isnull[1] = {false};

	while (*text)
	{
		char	   *eol;
		int			len;

		eol = strchr(text, '\n');
		if (eol)
		{
			len = eol - text;

			eol++;
		}
		else
		{
			len = strlen(text);
			eol += len;
		}

		values[0] = PointerGetDatum(cstring_to_text_with_len(text, len));
		do_tup_output(tstate, values, isnull);
		pfree(DatumGetPointer(values[0]));
		text = eol;
	}
}
