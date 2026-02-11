subject_compare(const gchar *s1, const gchar *s2)
{
	gchar *str1, *str2;

	if (!s1 || !s2) return -1;
	if (!*s1 || !*s2) return -1;

	Xstrdup_a(str1, s1, return -1);
	Xstrdup_a(str2, s2, return -1);

	trim_subject_for_compare(str1);
	trim_subject_for_compare(str2);

	if (!*str1 || !*str2) return -1;

	return strcmp(str1, str2);
}
