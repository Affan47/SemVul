PyAubio_ArrayToCCvec (PyObject *input) {
  if (PyObject_TypeCheck (input, &Py_cvecType)) {
      return ((Py_cvec*)input)->o;
  } else {
      PyErr_SetString (PyExc_ValueError, "input array should be float32");
      return NULL;
  }
}
