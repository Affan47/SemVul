Wdifference(TableWrapper *left, TableWrapper *right)
{
  enum BucketFlag lflag, rflag;

  Dprint(("Wdifference\n"));
  if ((PyObject *)left == Py_None) {
    PyErr_SetString(PyExc_TypeError, "cannot difference from Py_None");
    return NULL;
  }

  if ((PyObject *)right == Py_None) {
    return (PyObject *) newWrapper(0, left->rep.flag);
  }
  rflag = right->rep.flag;
  lflag = left->rep.flag;


  if ( (rflag != lflag) && ((rflag == SETFLAG)||(lflag == SETFLAG)) ) {
    PyErr_SetString(PyExc_TypeError, "mixed difference not allowed with kjSet");
    return NULL;
  }
  return Wintdiff(left, right, 0, lflag);
}
