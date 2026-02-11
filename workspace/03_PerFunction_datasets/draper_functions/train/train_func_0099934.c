SetTimeStep( vtkIdType t )
{
  LSDynaMetaData* p = this->P;
  if ( p->CurrentState == t )
    {
    return;
    }


  if ( ! p->FileIsValid )
    {
    if ( p->Fam.GetDatabaseDirectory().empty() )
      {
      vtkErrorMacro( "You haven't set the LS-Dyna database directory!" );
      return;
      }

    p->Fam.SetDatabaseBaseName( "/d3plot" );
    p->Fam.ScanDatabaseDirectory();
    if ( p->Fam.GetNumberOfFiles() < 1 )
      {
      p->FileIsValid = 0;
      return;
      }
    p->Fam.DetermineStorageModel();
    p->MaxFileLength = p->FileSizeFactor*512*512*p->Fam.GetWordSize();
    p->FileIsValid = 1;


    this->ReadHeaderInformation( 0 );


    this->ScanDatabaseTimeSteps();
    }


  if ( t >= 0 && t < (int) p->TimeValues.size() )
    {
    if ( p->Fam.GetCurrentAdaptLevel() != p->Fam.TimeAdaptLevel( t ) )
      {
      if ( this->ReadHeaderInformation( p->Fam.TimeAdaptLevel( t ) ) == 0 )
        {


        return;
        }
      }
    }

  p->CurrentState = t;
  this->Modified();
}
