Callback_Print_Attrs(char *word[], hexchat_event_attrs *attrs, void *userdata)
{
	Hook *hook = (Hook *) userdata;
	PyObject *retobj;
	PyObject *word_list;
	PyObject *word_eol_list;
	PyObject *attributes;
	char **word_eol;
	char *word_eol_raw;
	int listsize = 0;
	int next = 0;
	int i;
	int ret = 0;
	PyObject *plugin;


	word += 1;


	while (word[listsize] && word[listsize][0])
		listsize++;
	word_eol = (char **) g_malloc(sizeof(char*)*(listsize+1));
	if (word_eol == NULL) {
		hexchat_print(ph, "Not enough memory to alloc word_eol "
				"for python plugin callback.");
		return 0;
	}

	memcpy(word_eol, word, listsize*sizeof(char*));
	word_eol[listsize] = NULL;

	word_eol_raw = g_strjoinv(" ", word_eol);
	if (word_eol_raw == NULL) {
		hexchat_print(ph, "Not enough memory to alloc word_eol_raw "
				"for python plugin callback.");
		return 0;
	}

	for (i = 0; i != listsize; i++) {
		word_eol[i] = word_eol_raw+next;
		next += strlen(word[i])+1;
	}
	word_eol[i] = "";

	plugin = hook->plugin;
	BEGIN_PLUGIN(plugin);

	word_list = Util_BuildList(word);
	if (word_list == NULL) {
		g_free(word_eol_raw);
		g_free(word_eol);
		END_PLUGIN(plugin);
		return 0;
	}
	word_eol_list = Util_BuildList(word_eol);
	if (word_eol_list == NULL) {
		g_free(word_eol_raw);
		g_free(word_eol);
		Py_DECREF(word_list);
		END_PLUGIN(plugin);
		return 0;
	}

	attributes = Attribute_New(attrs);

	retobj = PyObject_CallFunction(hook->callback, "(OOOO)", word_list,
					    word_eol_list, hook->userdata, attributes);

	Py_DECREF(word_list);
	Py_DECREF(word_eol_list);
	Py_DECREF(attributes);

	g_free(word_eol_raw);
	g_free(word_eol);
	if (retobj == Py_None) {
		ret = HEXCHAT_EAT_NONE;
		Py_DECREF(retobj);
	} else if (retobj) {
		ret = PyLong_AsLong(retobj);
		Py_DECREF(retobj);
	} else {
		PyErr_Print();
	}

	END_PLUGIN(plugin);

	return ret;
}
