GetProperty()
{
  if (this->Property == NULL)
    {
    this->Property = vtkImageProperty::New();
    this->Property->Register(this);
    this->Property->Delete();
    }
  return this->Property;
}
