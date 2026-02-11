TrySDDP(const char* method)
{

  if(!this->GetExecutive())
    {
    vtkTrivialProducer* tp = vtkTrivialProducer::New();
    tp->SetOutput(this);
    tp->FastDelete();
    }


  if(SDDP* sddp = SDDP::SafeDownCast(this->GetExecutive()))
    {
    return sddp;
    }
  else if(method)
    {
    vtkErrorMacro("Method " << method << " cannot be called unless the "
                  "data object is managed by a "
                  "vtkStreamingDemandDrivenPipeline.");
    }
  return 0;
}
