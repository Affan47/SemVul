Datum_split_(Datum *self, void *delimsList)
{
	List *delims = (List *)delimsList;
	List *results = List_new();
	size_t i, last = 0;

	for (i = 0; i < self->size; i ++)
	{
		Datum d = Datum_datumAt_(self, i);
		size_t j;

		for (j = 0; j < (size_t)List_size(delims); j ++)
		{
			Datum *delim = (Datum *)List_at_(delims, j);

			if (Datum_beginsWith_(&d, delim))
			{
                                List_append_(results, Datum_newFrom_to_(self, last, i));

				last = i + delim->size;
				i = last - 1;
				break;
			}
		}
	}

	if (last != self->size)
	{
		List_append_(results, Datum_newFrom_to_(self, last, self->size));
	}

	return results;
}
