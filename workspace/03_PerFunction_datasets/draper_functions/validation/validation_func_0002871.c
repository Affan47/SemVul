DeepCopy(vtkDataObject *dataObject)
{
  vtkUnstructuredGrid *grid = vtkUnstructuredGrid::SafeDownCast(dataObject);

  if ( grid != NULL )
    {
    if ( this->Connectivity )
      {
      this->Connectivity->UnRegister(this);
      this->Connectivity = NULL;
      }
    if (grid->Connectivity)
      {
      this->Connectivity = vtkCellArray::New();
      this->Connectivity->DeepCopy(grid->Connectivity);
      this->Connectivity->Register(this);
      this->Connectivity->Delete();
      }

    if ( this->Links )
      {
      this->Links->UnRegister(this);
      this->Links = NULL;
      }
    if ( this->Types )
      {
      this->Types->UnRegister(this);
      this->Types = NULL;
      }
    if (grid->Types)
      {
      this->Types = vtkUnsignedCharArray::New();
      this->Types->DeepCopy(grid->Types);
      this->Types->Register(this);
      this->Types->Delete();
      }

    if ( this->Locations )
      {
      this->Locations->UnRegister(this);
      this->Locations = NULL;
      }
    if (grid->Locations)
      {
      this->Locations = vtkIdTypeArray::New();
      this->Locations->DeepCopy(grid->Locations);
      this->Locations->Register(this);
      this->Locations->Delete();
      }

    if ( this->Faces )
      {
      this->Faces->UnRegister(this);
      this->Faces = NULL;
      }
    if (grid->Faces)
      {
      this->Faces = vtkIdTypeArray::New();
      this->Faces->DeepCopy(grid->Faces);
      this->Faces->Register(this);
      this->Faces->Delete();
      }

    if ( this->FaceLocations )
      {
      this->FaceLocations->UnRegister(this);
      this->FaceLocations = NULL;
      }
    if (grid->FaceLocations)
      {
      this->FaceLocations = vtkIdTypeArray::New();
      this->FaceLocations->DeepCopy(grid->FaceLocations);
      this->FaceLocations->Register(this);
      this->FaceLocations->Delete();
      }
    }


  this->vtkPointSet::DeepCopy(dataObject);


  if (grid && grid->Links)
    {
    this->BuildLinks();
    }
}
