app_pango_strip_markup(const Glib::ustring& str, Glib::ustring& stripped)
{
	gchar* gstripped = 0;
	bool ok = false;
	if (pango_parse_markup(str.c_str(), -1, 0, NULL, &gstripped, NULL, NULL) && gstripped) {
		stripped = gstripped;
		ok = true;
	}
	g_free(gstripped);


	return ok;
}
