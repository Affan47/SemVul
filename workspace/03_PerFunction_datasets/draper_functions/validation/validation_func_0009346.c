expand_combo(const char *start, const char *end, GSList **out)
{
        KEY_REC *rec;
	KEYINFO_REC *info;
        GSList *tmp, *tmp2, *list, *copy, *newout;
	char *str, *p;

	if (start == end) {

		expand_out_char(*out, *start);
                return TRUE;
	}

	info = key_info_find("key");
	if (info == NULL)
		return FALSE;


        list = NULL;
	str = g_strndup(start, (int) (end-start)+1);
	for (tmp = info->keys; tmp != NULL; tmp = tmp->next) {
		KEY_REC *rec = tmp->data;

		if (strcmp(rec->data, str) == 0)
                        list = g_slist_append(list, rec);
	}

	if (list == NULL) {


		for (p = str; *p != '\0'; p++)
			expand_out_char(*out, *p);
		g_free(str);
		return TRUE;
	}
	g_free(str);

	if (list->next == NULL) {

                rec = list->data;
		g_slist_free(list);
		return expand_key(rec->key, out);
	}


        newout = NULL;
	for (tmp = list->next; tmp != NULL; tmp = tmp->next) {
		KEY_REC *rec = tmp->data;

		copy = NULL;
		for (tmp2 = *out; tmp2 != NULL; tmp2 = tmp2->next) {
			GString *str = tmp2->data;
                        copy = g_slist_append(copy, g_string_new(str->str));
		}

		if (!expand_key(rec->key, &copy)) {

                        expand_out_free(copy);
		} else {
                        newout = g_slist_concat(newout, copy);
		}
	}

        rec = list->data;
	g_slist_free(list);
	if (!expand_key(rec->key, out)) {

		expand_out_free(*out);
	}

	*out = g_slist_concat(*out, newout);
        return *out != NULL;
}
