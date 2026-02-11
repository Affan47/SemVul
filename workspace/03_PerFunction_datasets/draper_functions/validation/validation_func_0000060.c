p_cs_render (PyObject *self, PyObject *args)
{
  CSObject *co = (CSObject *)self;
  NEOERR *err;
  STRING str;
  PyObject *rv;

  string_init(&str);
  err = cs_render (co->data, &str, render_cb);
  if (err) return p_neo_error(err);
  rv = Py_BuildValue ("s", str.buf);
  string_clear (&str);
  return rv;
}
