py_merge_entries(PyObject *self, PyObject *args)
{
	PyObject *path, *tree1, *tree2, **entries1 = NULL, **entries2 = NULL;
	PyObject *e1, *e2, *pair, *result = NULL;
	Py_ssize_t path_len, n1 = 0, n2 = 0, i1 = 0, i2 = 0;
	char *path_str;
	int cmp;

	if (!PyArg_ParseTuple(args, "OOO", &path, &tree1, &tree2))
		return NULL;

	path_str = PyString_AsString(path);
	if (!path_str) {
		PyErr_SetString(PyExc_TypeError, "path is not a string");
		return NULL;
	}
	path_len = PyString_GET_SIZE(path);

	entries1 = tree_entries(path_str, path_len, tree1, &n1);
	if (!entries1)
		goto error;
	entries2 = tree_entries(path_str, path_len, tree2, &n2);
	if (!entries2)
		goto error;

	result = PyList_New(n1 + n2);
	if (!result)
		goto error;


	Py_SIZE(result) = 0;

	while (i1 < n1 && i2 < n2) {
		cmp = entry_path_cmp(entries1[i1], entries2[i2]);
		if (PyErr_Occurred())
			goto error;
		if (!cmp) {
			e1 = entries1[i1++];
			e2 = entries2[i2++];
		} else if (cmp < 0) {
			e1 = entries1[i1++];
			e2 = null_entry;
		} else {
			e1 = null_entry;
			e2 = entries2[i2++];
		}
		pair = PyTuple_Pack(2, e1, e2);
		if (!pair)
			goto error;
		PyList_SET_ITEM(result, Py_SIZE(result)++, pair);
	}

	while (i1 < n1) {
		pair = PyTuple_Pack(2, entries1[i1++], null_entry);
		if (!pair)
			goto error;
		PyList_SET_ITEM(result, Py_SIZE(result)++, pair);
	}
	while (i2 < n2) {
		pair = PyTuple_Pack(2, null_entry, entries2[i2++]);
		if (!pair)
			goto error;
		PyList_SET_ITEM(result, Py_SIZE(result)++, pair);
	}
	goto done;

error:
	Py_XDECREF(result);
	result = NULL;

done:
	free_objects(entries1, n1);
	free_objects(entries2, n2);
	return result;
}
