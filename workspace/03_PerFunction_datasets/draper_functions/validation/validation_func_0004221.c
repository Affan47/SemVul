func_exists (struct _ESExp *f,
             gint argc,
             struct _ESExpResult **argv,
             gpointer data)
{
	GList **list = data;
	ESExpResult *r;

	if (argc == 1
	    && argv[0]->type == ESEXP_RES_STRING) {
		gchar *propname = argv[0]->value.string;
		EContactField field = e_contact_field_id (propname);

		if (field)
			*list = g_list_prepend (*list, e_book_query_field_exists (field));
		else
			*list = g_list_prepend (*list, e_book_query_vcard_field_exists (propname));
	}

	r = e_sexp_result_new (f, ESEXP_RES_BOOL);
	r->value.boolean = FALSE;

	return r;
}
