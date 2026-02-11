SetLookupTable(vtkScalarsToColors *l)
{
  vtkSetObjectBodyMacro(LookupTable, vtkScalarsToColors, l);
  this->LookupTable = l;
  if (this->ColorMap)
    {
    this->ColorMap->SetLookupTable(this->LookupTable);
    }
}
