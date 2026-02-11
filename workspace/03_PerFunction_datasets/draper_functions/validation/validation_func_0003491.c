ReportReferences(vtkGarbageCollector* collector)
{
  this->Superclass::ReportReferences(collector);
  for(int i=0; i < this->NumberOfInformationObjects; ++i)
    {
    vtkGarbageCollectorReport(collector, this->Internal->Vector[i], "Entry");
    }
}
