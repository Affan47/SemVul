gdpy_dirfile_getconstants(struct gdpy_dirfile_t* self,
    void* args, void* keys)
{
  dtrace("%p, %p, %p", self, args, keys);

  int i;
  char* keywords[] = {"return_type", NULL};
  const char** fields;
  const char* values;
  gd_type_t return_type;

  if (!PyArg_ParseTupleAndKeywords(args, keys,
        "i:pygetdata.dirfile.constants", keywords, &return_type))
  {
    dreturn("%p", NULL);
    return NULL;
  }

  fields = gd_field_list_by_type(self->D, GD_CONST_ENTRY);

  PYGD_CHECK_ERROR(self->D, NULL);

  values = gd_constants(self->D, return_type);

  PYGD_CHECK_ERROR(self->D, NULL);

  PyObject* list = PyList_New(0);

  for (i = 0; fields[i] != NULL; ++i)
    PyList_Append(list, Py_BuildValue("sN", fields[i],
          gdpy_convert_to_pyobj(values + i * GD_SIZE(return_type),
            return_type)));

  dreturn("%p", list);
  return list;
}
