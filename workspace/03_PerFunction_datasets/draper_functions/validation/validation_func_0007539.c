AddObserver(unsigned long event, vtkCommand *cmd, float p)
{
  if (!this->SubjectHelper)
    {
    this->SubjectHelper = new vtkSubjectHelper;
    }
  return this->SubjectHelper->AddObserver(event,cmd, p);
}
