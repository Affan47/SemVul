PythonShutdown(void)
{
    Py_Finalize();

#ifdef WIN32
    if (python_dir) {
        g_free(python_dir);
        python_dir = NULL;
    }
#endif
    if (py_gnubg_module) {
        Py_DECREF(py_gnubg_module);
    }

    py_gnubg_module = NULL;
}
