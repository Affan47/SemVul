filter_matches(PyObject * self, PyObject * args)
{
  PyObject * p;
  float threshold;

  if (!PyArg_ParseTuple(args, "Of", &p, &threshold)) {
    return NULL;
  }

  ImmutableComparison * c = (ImmutableComparison *) PyCObject_AsVoidPtr(p);
  ImmutableComparison * f = c->filter_by_threshold(threshold);

  return PyCObject_FromVoidPtr(f, cleanup_ImmComparison);
}
