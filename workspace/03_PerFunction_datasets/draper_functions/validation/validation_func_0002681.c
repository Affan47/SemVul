PyvtkSQLQuery_BindParameter_s4(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "BindParameter");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkSQLQuery *op = static_cast<vtkSQLQuery *>(vp);

  int temp0;
  double temp1;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(2) &&
      ap.GetValue(temp0) &&
      ap.GetValue(temp1))
    {
    bool tempr = (ap.IsBound() ?
      op->BindParameter(temp0, temp1) :
      op->vtkSQLQuery::BindParameter(temp0, temp1));

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildValue(tempr);
      }
    }

  return result;
}
