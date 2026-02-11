error_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	if (a[0]->type == GEL_STRING_NODE) {
		gel_errorout ("%s", a[0]->str.str);
	} else {
		GelOutput *gelo = gel_output_new();
		char *s;
		gel_output_setup_string (gelo, 0, NULL);
		gel_pretty_print_etree (gelo, a[0]);
		s = gel_output_snarf_string (gelo);
		gel_output_unref (gelo);
		gel_errorout ("%s", s != NULL ? s : "");
		g_free (s);
	}
	return gel_makenum_null();
}
