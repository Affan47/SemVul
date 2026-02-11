__pyx_tp_new_13pybloomfilter_BloomFilter(PyTypeObject *t, PyObject *a, PyObject *k) {
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  if (unlikely(__pyx_pw_13pybloomfilter_11BloomFilter_1__cinit__(o, a, k) < 0)) {
    Py_DECREF(o); o = 0;
  }
  return o;
}
