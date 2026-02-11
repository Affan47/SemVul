ClipDataSet( vtkDataSet * pDataSet,
     vtkDataArray * clipAray, vtkUnstructuredGrid * unstruct )
{
  vtkClipDataSet * clipData = vtkClipDataSet::New();
  clipData->SetInput( pDataSet );
  clipData->SetValue( this->Value );
  clipData->SetInsideOut( this->InsideOut );
  clipData->SetClipFunction( this->ClipFunction );
  clipData->SetUseValueAsOffset( this->UseValueAsOffset );
  clipData->SetGenerateClipScalars( this->GenerateClipScalars );

  if ( !this->ClipFunction )
    {
    pDataSet->GetPointData()->SetScalars( clipAray );
    }

  clipData->Update();
  unstruct->ShallowCopy( clipData->GetOutput() );

  clipData->Delete();
  clipData = NULL;
}
