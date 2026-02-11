gtop_proc_segment (PyObject *self, PyObject *args)
{
    glibtop_proc_segment buf;
    PyObject *d;
    guint pid;

    if (!PyArg_ParseTuple (args, "I", &pid))
        return NULL;

    glibtop_get_proc_segment (&buf, pid);

    d = PyDict_New ();

    my_dict_add_and_decref (d, "text_rss",   PyL_ULL (buf.text_rss));
    my_dict_add_and_decref (d, "shlib_rss",  PyL_ULL (buf.shlib_rss));
    my_dict_add_and_decref (d, "data_rss",   PyL_ULL (buf.data_rss));
    my_dict_add_and_decref (d, "stack_rss",  PyL_ULL (buf.stack_rss));
    my_dict_add_and_decref (d, "dirty_size", PyL_ULL (buf.dirty_size));
    my_dict_add_and_decref (d, "start_code", PyL_ULL (buf.start_code));
    my_dict_add_and_decref (d, "end_code",   PyL_ULL (buf.end_code));
    my_dict_add_and_decref (d, "start_stack",PyL_ULL (buf.start_stack));

    return _struct_new (d);
}
