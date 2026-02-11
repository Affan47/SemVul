Print(ostream& os, vtkInformation* info)
{

  if(this->Has(info))
    {
    double* value = this->Get(info);
    int length = this->Length(info);
    const char* sep = "";
    for(int i=0; i < length; ++i)
      {
      os << sep << value[i];
      sep = " ";
      }
    }
}
