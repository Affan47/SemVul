Handle(int index)
{
  if (index == 0)
    return this->handle;
  else if (index == 1)
  {
    if (this->is_new)
      return (void*)&this->cinfo;
    else
      return (void*)&this->dinfo;
  }
  else
    return NULL;
}
