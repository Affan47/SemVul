UpdateOutputData( DataObject * itkNotUsed(output) )
{


  if ( m_Updating )
    {
    return;
    }


  this->PrepareOutputs();


  m_Updating = true;
  if ( m_Inputs.size() == 1 )
    {
    if ( this->GetPrimaryInput() )
      {
      this->GetPrimaryInput()->UpdateOutputData();
      }
    }
  else
    {
    for ( DataObjectPointerMap::iterator it=m_Inputs.begin(); it != m_Inputs.end(); ++it )
      {
      if ( it->second )
        {
        it->second->PropagateRequestedRegion();
        it->second->UpdateOutputData();
        }
      }
    }


  this->CacheInputReleaseDataFlags();


  this->InvokeEvent( StartEvent() );


  m_AbortGenerateData = false;
  m_Progress = 0.0f;

  try
    {
    this->GenerateData();
    }
  catch ( ProcessAborted & excp )
    {
    this->InvokeEvent( AbortEvent() );
    this->ResetPipeline();
    this->RestoreInputReleaseDataFlags();
    throw &excp;
    }
  catch (...)
    {
    this->ResetPipeline();
    this->RestoreInputReleaseDataFlags();
    throw;
    }


  if ( m_AbortGenerateData )
    {
    this->UpdateProgress(1.0f);
    }


  this->InvokeEvent( EndEvent() );


  for ( DataObjectPointerMap::iterator it=m_Outputs.begin(); it != m_Outputs.end(); ++it )
    {
    if ( it->second )
      {
      it->second->DataHasBeenGenerated();
      }
    }


  this->RestoreInputReleaseDataFlags();


  this->ReleaseInputs();


  m_Updating = false;
}
