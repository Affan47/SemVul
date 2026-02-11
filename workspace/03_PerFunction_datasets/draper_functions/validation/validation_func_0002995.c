PyState_AddModule(PyObject* module, struct PyModuleDef* def)
{
    Py_ssize_t index;
    PyInterpreterState *state = PyThreadState_GET()->interp;
    if (!def) {
        Py_FatalError("PyState_AddModule: Module Definition is NULL");
        return -1;
    }
    index = def->m_base.m_index;
    if (state->modules_by_index) {
        if(PyList_GET_SIZE(state->modules_by_index) >= index) {
            if(module == PyList_GET_ITEM(state->modules_by_index, index)) {
                Py_FatalError("PyState_AddModule: Module already added!");
                return -1;
            }
        }
    }
    return _PyState_AddModule(module, def);
}
