test_strlcpy ()
{
	const gchar *src = "onetwothree";
	gchar *dest;
	gsize i;

	dest = g_malloc (strlen (src) + 1);
	memset (dest, 0, strlen (src) + 1);
	i = g_strlcpy (dest, src, (gsize)-1);
	if (i != strlen (src))
		return FAILED ("Test1 got %d", i);

	if (0 != strcmp (dest, src))
		return FAILED ("Src and dest not equal");

	i = g_strlcpy (dest, src, 3);
	if (i != strlen (src))
		return FAILED ("Test1 got %d", i);
	if (0 != strcmp (dest, "on"))
		return FAILED ("Test2");

	i = g_strlcpy (dest, src, 1);
	if (i != strlen (src))
		return FAILED ("Test3 got %d", i);
	if (*dest != '\0')
		return FAILED ("Test4");

	i = g_strlcpy (dest, src, 12345);
	if (i != strlen (src))
		return FAILED ("Test4 got %d", i);
	if (0 != strcmp (dest, src))
		return FAILED ("Src and dest not equal 2");
	g_free (dest);


	dest = g_filename_from_utf8 (NUMBERS, strlen (NUMBERS), NULL, NULL, NULL);
	if (0 != strcmp (dest, NUMBERS))
		return FAILED ("problem [%s] and [%s]", dest, NUMBERS);
	g_free (dest);

	return OK;
}
