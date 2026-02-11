HasTranslucentPolygonalGeometry()
{
  int result;


  if ( this->SelectedLODIndex < 0 ||
       this->SelectedLODIndex >= this->NumberOfEntries )
    {
    vtkErrorMacro( << "Index out of range!" );
    return 0;
    }


  if ( this->LODs[this->SelectedLODIndex].ID == VTK_INDEX_NOT_IN_USE )
    {
    vtkErrorMacro( << "Index not valid!" );
    return 0;
    }

  result = this->LODs[this->SelectedLODIndex].Prop3D->HasTranslucentPolygonalGeometry();

  return result;
}
