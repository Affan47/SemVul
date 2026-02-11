lam_wrap_strip_white(string& str)
{
  int start, end, size(str.size());


  for (start = 0; start < size; ++start)
    if (!isspace(str[start]))
      break;


  for (end = start; end < size; ++end)
    if (isspace(str[end]))
      break;

  str = str.substr(start, end);
}
