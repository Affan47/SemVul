in_string::~in_string()
{
  if (base)
  {

    for (uint i=0 ; i < count ; i++)
      ((String*) base)[i].free();
  }
}
