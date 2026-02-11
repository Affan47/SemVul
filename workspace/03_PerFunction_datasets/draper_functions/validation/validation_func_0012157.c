GetCurrentKey()
{
  if (this->IsDoneWithTraversal())
    {
    return 0;
    }

  return this->Internal->Iterator->first;
}
