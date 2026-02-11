GlobalHotkey_unbind (GlobalHotkey *self,
                     PyObject     *args)
{
  char *key;

  if (!PyArg_ParseTuple (args, "s", &key))
    return NULL;

  keybinder_unbind (key, caller);
  PyDict_DelItemString (self->binded, key);
  return Py_BuildValue ("");
}
