vtkPythonGetValue(PyObject *o, char &a)
{
  static const char exctext[] = "a string of length 1 is required";
  const char *b;
  if (vtkPythonGetStringValue(o, b, exctext))
    {
    if (b[0] == '\0' || b[1] == '\0')
      {
      a = b[0];
      return true;
      }
    PyErr_SetString(PyExc_TypeError, exctext);
    }
  return false;
}
