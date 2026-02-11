contains(PyObject * self, PyObject * args)
{
  PyObject * ret = NULL;
  PyObject * big_p, * small_p;

  if (!PyArg_ParseTuple(args, "OO", &big_p, &small_p)) {
    return NULL;
  }

  const ImmutableComparison * big, * small;

  big = (ImmutableComparison *) PyCObject_AsVoidPtr(big_p);
  small = (ImmutableComparison *) PyCObject_AsVoidPtr(small_p);

  int answer = 0;
  try {
    if (big->contains(*small)) {
      answer = 1;
    }
    ret = Py_BuildValue("i", answer);
  } catch(paircomp_exception & e) {
    PyErr_SetString(PaircompParserError, e.error_msg.c_str());

    ret = NULL;
  }

  return ret;
}
