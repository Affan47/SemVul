mono_test_marshal_byref_struct (simplestruct *ss, int a, int b, int c, char *d)
{
	gboolean res = (ss->a == a && ss->b == b && ss->c == c && strcmp (ss->d, d) == 0);

	marshal_free ((char*)ss->d);

	ss->a = !ss->a;
	ss->b = !ss->b;
	ss->c = !ss->c;
	ss->d = marshal_strdup ("DEF");

	return res ? 0 : 1;
}
