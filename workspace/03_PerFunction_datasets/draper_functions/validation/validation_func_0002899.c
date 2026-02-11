eio_input_field(fstream& str,
		     int& name, int& type,
		     int& len, int* fields, double* values)
{
  int i;
  str >> name >> type >> len;
  for(i = 0; i < len; ++i)
    {
      str >> fields[i];
    }
  for(i = 0; i < len; ++i)
    {
      str >> values[i];
    }
}
