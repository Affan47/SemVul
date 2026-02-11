ReadUntil(std::ifstream& in, char until)
{
  char c = 0;
  while(in.get(c) && c != until)
    {
    }
  if(c != until)
    {
    return false;
    }
  return true;
}
