ugly_memdump(void *ptr, size_t size)
{
    STRPTR data = (STRPTR) ptr;


    if (size > 16)
    {
	size = 16;
    }

    fprintf(stderr, "  %p:", ptr);
    if (data)
    {
	size_t i;


	for (i = 0; i < size; i++)
	{
	    if (!(i % 4))
	    {
		fprintf(stderr, " ");
	    }
	    fprintf(stderr, "%02x", data[i]);

	}


	while (i < 16)
	{
	    if (!(i % 4))
	    {
		fprintf(stderr, " ");
	    }
	    fprintf(stderr, "  ");
	    i++;
	}

	fprintf(stderr, "  \"");

	for (i = 0; i < size; i++)
	{
	    if (data[i] < ' ')
	    {
		fprintf(stderr, ".");
	    }
	    else
	    {
		fprintf(stderr, "%c", data[i]);
	    }
	}
	fprintf(stderr, "\"\n");

    }
    else
	fprintf(stderr, "NULL\n");

}
