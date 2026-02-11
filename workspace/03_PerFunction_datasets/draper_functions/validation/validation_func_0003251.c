PyvtkAbstractMapper3D_GetClippingPlaneInDataCoords(PyObject *self, PyObject *args)
{
  vtkPythonArgs ap(self, args, "GetClippingPlaneInDataCoords");
  vtkObjectBase *vp = ap.GetSelfPointer(self, args);
  vtkAbstractMapper3D *op = static_cast<vtkAbstractMapper3D *>(vp);

  vtkMatrix4x4 *temp0 = NULL;
  int temp1;
  double temp2[4];
  double save2[4];
  const int size2 = 4;
  PyObject *result = NULL;

  if (op && ap.CheckArgCount(3) &&
      ap.GetVTKObject(temp0, "vtkMatrix4x4") &&
      ap.GetValue(temp1) &&
      ap.GetArray(temp2, size2))
    {
    ap.SaveArray(temp2, save2, size2);

    if (ap.IsBound())
      {
      op->GetClippingPlaneInDataCoords(temp0, temp1, temp2);
      }
    else
      {
      op->vtkAbstractMapper3D::GetClippingPlaneInDataCoords(temp0, temp1, temp2);
      }

    if (ap.ArrayHasChanged(temp2, save2, size2) &&
        !ap.ErrorOccurred())
      {
      ap.SetArray(2, temp2, size2);
      }

    if (!ap.ErrorOccurred())
      {
      result = ap.BuildNone();
      }
    }

  return result;
}
