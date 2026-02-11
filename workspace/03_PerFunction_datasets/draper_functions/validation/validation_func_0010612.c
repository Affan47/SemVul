CleanupArgs()
{
  if (this->Args)
    {
    char** a = this->Args;
    while (*a)
      {
      delete [] (*a);
      a++;
      }
    delete [] this->Args;
    this->Args = 0;
    }
}
