glade_python_init_pygtk_check (gint req_major, gint req_minor, gint req_micro)
{
	PyObject *gobject, *mdict, *version;
	int found_major, found_minor, found_micro;

	init_pygobject();

	gobject = PyImport_ImportModule("gobject");
	mdict = PyModule_GetDict(gobject);
        version = PyDict_GetItemString(mdict, "pygtk_version");
	if (!version)
	{
		PyErr_SetString(PyExc_ImportError, "PyGObject version too old");
		return;
	}
	if (!PyArg_ParseTuple(version, "iii", &found_major, &found_minor, &found_micro))
		return;
	if (req_major != found_major || req_minor >  found_minor ||
	    (req_minor == found_minor && req_micro > found_micro))
	{
		PyErr_Format(PyExc_ImportError,
                     "PyGObject version mismatch, %d.%d.%d is required, "
                     "found %d.%d.%d.", req_major, req_minor, req_micro,
                     found_major, found_minor, found_micro);
		return;
	}
}
