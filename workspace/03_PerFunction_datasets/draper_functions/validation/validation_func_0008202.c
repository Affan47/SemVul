RequestData(
        vtkInformation *,
        vtkInformationVector **input,
        vtkInformationVector *output)
{
  vtkDataObject *tmpDataObj;

  tmpDataObj
    = input[0]->GetInformationObject(0)->Get(vtkDataObject::DATA_OBJECT());
  vtkUnstructuredGrid *usgIn
    = vtkUnstructuredGrid::SafeDownCast(tmpDataObj);

  tmpDataObj
    = output->GetInformationObject(0)->Get(vtkDataObject::DATA_OBJECT());
  vtkUnstructuredGrid *usgOut
    = vtkUnstructuredGrid::SafeDownCast(tmpDataObj);


  if (usgIn==NULL || usgOut==NULL
     || usgIn->GetNumberOfCells()==0
     || usgIn->GetNumberOfPoints()==0
     || usgIn->GetPointData()==NULL
     || usgIn->GetPointData()->GetNumberOfArrays()==0)
    {
    vtkWarningMacro("Filter data has not been configured correctly. Aborting.");
    return 1;
    }


  usgOut->ShallowCopy(usgIn);


  this->InterpolateFields(usgOut);

  return 1;
}
