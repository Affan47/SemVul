compare_direntry_scores (gconstpointer a,
                         gconstpointer b)
{
	const struct ico_direntry_data *ia = a;
	const struct ico_direntry_data *ib = b;


	return ib->ImageScore - ia->ImageScore;
}
