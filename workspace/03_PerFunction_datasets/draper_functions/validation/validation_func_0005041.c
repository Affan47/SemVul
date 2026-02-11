PyEval_GetFuncName(PyObject *func)
{
    if (PyMethod_Check(func))
        return PyEval_GetFuncName(PyMethod_GET_FUNCTION(func));
    else if (PyFunction_Check(func))
        return PyString_AsString(((PyFunctionObject*)func)->func_name);
    else if (PyCFunction_Check(func))
        return ((PyCFunctionObject*)func)->m_ml->ml_name;
    else if (PyClass_Check(func))
        return PyString_AsString(((PyClassObject*)func)->cl_name);
    else if (PyInstance_Check(func)) {
        return PyString_AsString(
            ((PyInstanceObject*)func)->in_class->cl_name);
    } else {
        return func->ob_type->tp_name;
    }
}
