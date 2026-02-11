GetColumnTypeFromHandle(
  int tblHandle, int colHandle )
{
  if ( tblHandle < 0 || tblHandle >= this->GetNumberOfTables() )
    {
    vtkErrorMacro( "Cannot get type of a column in non-existent table " << tblHandle );
    return -1;
    }

  if ( colHandle < 0 || colHandle >= static_cast<int>( this->Internals->Tables[tblHandle].Columns.size() ) )
    {
    vtkErrorMacro( "Cannot get type of non-existent column " << colHandle << " in table " << tblHandle );
    return -1;
    }

  return static_cast<int>( this->Internals->Tables[tblHandle].Columns[colHandle].Type );
}
