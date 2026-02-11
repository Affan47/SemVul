wordzero(wstring const &chunk)
{
  for(unsigned int i = 0, limit = chunk.size(); i != limit ;i++)
  {
    if(chunk[i] == L'\\')
    {
      i++;
    }
    else if(chunk[i] == L'{')
    {
      return chunk.substr(0, i);
    }
  }

  return L"";
}
