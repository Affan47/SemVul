DisableLOD( int id )
{
  int index = this->ConvertIDToIndex( id );

  if ( index == VTK_INVALID_LOD_INDEX || index == VTK_INDEX_NOT_IN_USE )
    {
    return;
    }

  this->LODs[index].State = 0;
}
