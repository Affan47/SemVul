get_StringIO_instance(void)
{
  PyObject *module_StringIO = NULL;
  PyObject *class_StringIO = NULL;
  PyObject *inst_StringIO = NULL;

  module_StringIO = PyImport_ImportModule("cStringIO");
  if(!module_StringIO) {
    debug_print("Error getting traceback: Could not import module cStringIO\n");
    goto done;
  }

  class_StringIO = PyObject_GetAttrString(module_StringIO, "StringIO");
  if(!class_StringIO) {
    debug_print("Error getting traceback: Could not get StringIO class\n");
    goto done;
  }

  inst_StringIO = PyObject_CallObject(class_StringIO, NULL);
  if(!inst_StringIO) {
    debug_print("Error getting traceback: Could not create an instance of the StringIO class\n");
    goto done;
  }

done:
  Py_XDECREF(module_StringIO);
  Py_XDECREF(class_StringIO);

  return inst_StringIO;
}
