tetravex_main (gchar** args, int args_length1) {
	gint result = 0;
	Tetravex* _tmp0_;
	Tetravex* app;
	gchar** _tmp1_;
	gint _tmp1__length1;
	gint _tmp2_ = 0;
	setlocale (LC_ALL, "");
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	_tmp0_ = tetravex_new ();
	app = _tmp0_;
	_tmp1_ = args;
	_tmp1__length1 = args_length1;
	_tmp2_ = g_application_run ((GApplication*) app, _tmp1__length1, _tmp1_);
	result = _tmp2_;
	_g_object_unref0 (app);
	return result;
}
