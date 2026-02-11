get_arg_names_for_macro (Method *m)
{
	const char *sep;
	GList *li;
	GString *gs = g_string_new(NULL);
	sep = "";
	for(li=m->args;li;li=g_list_next(li)) {
		FuncArg *arg = li->data;
		g_string_sprintfa (gs, "%s___%s", sep, arg->name);
		sep = ",";
	}
	return g_string_free (gs, FALSE);
}
