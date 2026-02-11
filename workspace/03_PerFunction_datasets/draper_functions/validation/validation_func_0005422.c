values_count(void)
{
	g_assert(values_managed >= 0);

	return (size_t) values_managed;
}
