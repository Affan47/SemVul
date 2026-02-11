PyCurses_IntrFlush(PyObject *self, PyObject *args)
{
    int ch;

    PyCursesInitialised;

    switch(PyTuple_Size(args)) {
    case 1:
        if (!PyArg_ParseTuple(args,"i;True(1), False(0)",&ch)) return NULL;
        break;
    default:
        PyErr_SetString(PyExc_TypeError, "intrflush requires 1 argument");
        return NULL;
    }

    return PyCursesCheckERR(intrflush(NULL,ch), "intrflush");
}
