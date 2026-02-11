ConstructCells(vtkDataObject *input,
                                                 vtkUnstructuredGrid *ug)
{
  int i, *types, typesAllocated=0;
  vtkDataArray *fieldArray[2];
  int ncells;
  vtkFieldData *fd=input->GetFieldData();

  fieldArray[0] = vtkFieldDataToAttributeDataFilter::GetFieldArray(
    fd, this->CellTypeArray,
    this->CellTypeArrayComponent);

   if ( fieldArray[0] == NULL )
    {
    vtkErrorMacro(<<"Can't find array requested for cell types");
    return 0;
    }

  vtkFieldDataToAttributeDataFilter::UpdateComponentRange(
    fieldArray[0],
    this->CellTypeComponentRange);
  ncells = this->CellTypeComponentRange[1] -
    this->CellTypeComponentRange[0] + 1;

  fieldArray[1] = vtkFieldDataToAttributeDataFilter::GetFieldArray(
    fd,
    this->CellConnectivityArray,
    this->CellConnectivityArrayComponent);
  if ( fieldArray[1] == NULL )
    {
    vtkErrorMacro(<<"Can't find array requested for cell connectivity");
    return 0;
    }


  if ( fieldArray[0] )
    {

    vtkDataArray *da=fieldArray[0];

    if ( da->GetDataType() == VTK_INT && da->GetNumberOfComponents() == 1 &&
         this->CellTypeArrayComponent == 0 &&
         this->CellTypeComponentRange[0] == 0 &&
         this->CellTypeComponentRange[1] == da->GetMaxId() )
      {
      types = static_cast<vtkIntArray *>(da)->GetPointer(0);
      }

    else
      {
      typesAllocated = 1;
      types = new int[ncells];
      for (i=this->CellTypeComponentRange[0];
           i <= this->CellTypeComponentRange[1]; i++)
        {
        types[i] =
          static_cast<int>(da->GetComponent(i,this->CellTypeArrayComponent));
        }
      }
    this->CellTypeComponentRange[0] = this->CellTypeComponentRange[1] = -1;


    if ( fieldArray[1] )
      {
      vtkFieldDataToAttributeDataFilter::UpdateComponentRange(fieldArray[1],
                                         this->CellConnectivityComponentRange);
      vtkCellArray *carray = this->ConstructCellArray(
        fieldArray[1],
        this->CellConnectivityArrayComponent,
        this->CellConnectivityComponentRange);
      if ( carray != NULL )
        {
        ug->SetCells(types,carray);
        carray->Delete();
        }
      this->CellConnectivityComponentRange[0]
        = this->CellConnectivityComponentRange[1] = -1;
      }
    if ( typesAllocated )
      {
      delete [] types;
      }
    }

  return ncells;
}
