utf7_closeb64 (GString *out, guint32 v, guint32 i)
{
	guint32 x;

	if (i > 0) {
		x = (v << (6 - i)) & 0x3f;
		g_string_append_c (out, utf7_alphabet[x]);
	}
	g_string_append_c (out, '-');
}
