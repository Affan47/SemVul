parser_richcompare(PyObject *left, PyObject *right, int op)
{
    int result;


    if (left == NULL || right == NULL) {
        PyErr_BadInternalCall();
        return NULL;
    }


    if (!PyST_Object_Check(left) || !PyST_Object_Check(right)) {
        Py_RETURN_NOTIMPLEMENTED;
    }

    if (left == right)

        result = 0;
    else
        result = parser_compare_nodes(((PyST_Object *)left)->st_node,
                                      ((PyST_Object *)right)->st_node);

    Py_RETURN_RICHCOMPARE(result, 0, op);
}
