_e2pcr_store (csize_t value, guchar *datastart)
{
	csize_t s = value;
	guint i;

    for (i = 0; i < sizeof (csize_t); i++)
	{
		*datastart++ = (guint8) s;
		s >>= 8;
    }
}
