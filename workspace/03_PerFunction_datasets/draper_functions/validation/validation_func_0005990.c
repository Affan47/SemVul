SetFunctionWeight(vtkImplicitFunction *f, double scale)
{
  int loc = this->FunctionList->IsItemPresent(f);
  if (! loc)
    {
    vtkWarningMacro("Function not found in function list");
    return;
    }
  loc--;

  if ( this->Weights->GetValue(loc) != scale )
    {
    this->Modified();
    this->Weights->SetValue(loc, scale);
    this->CalculateTotalWeight();
    }
}
