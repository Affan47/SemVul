AcquirePriority(vtkInformation * info)
{
  int priority;
  if (info && info->Has(TASK_PRIORITY()))
    {
    priority = info->Get(TASK_PRIORITY());
    }
  else
    {
    priority = this->CurrentPriority++;
    }
  return priority;
}
