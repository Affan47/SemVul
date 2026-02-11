gdpy_dirfile_getreference(struct gdpy_dirfile_t* self,
    void* closure)
{
  dtrace("%p, %p", self, closure);

  const char *ref = gd_reference(self->D, NULL);

  PYGD_CHECK_ERROR(self->D, NULL);

  PyObject* pyref = PyString_FromString(ref);

  dreturn("%p", pyref);
  return pyref;
}
