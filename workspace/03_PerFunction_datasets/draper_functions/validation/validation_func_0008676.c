RemoveField(const char *name)
{
  if ( !name )
    {
    return;
    }

  int i;
  for (i=NUM_ATTRIBUTES; i < this->NumberOfFields; i++)
    {
    if ( this->Fields[i] && !strcmp(this->Fields[i],name) )
      {
      delete [] this->Fields[i];
      this->Fields[i] = 0;
      this->FieldTypes[i] = -1;
      this->FieldComponents[i] = 0;

      delete this->FieldComponentsNames[i];
      this->FieldComponentsNames[i] = 0;

      this->FieldIndices[i] = -1;
      this->LUT[i] = 0;
      this->FieldInformation[i] = 0;
      return;
      }
    }
}
