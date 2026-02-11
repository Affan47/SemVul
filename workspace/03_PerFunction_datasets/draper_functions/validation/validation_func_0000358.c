get_terminal(string * s)
{
  int result;
  vector<string>::iterator it;
  it=find(terminal_table.begin(), terminal_table.end(), *s);
  if (it==terminal_table.end())
    {

      terminal_table.push_back(*s);
      result=terminal_table.size()-1;
    }
  else
    result=it-terminal_table.begin();

  return result+1;
}
