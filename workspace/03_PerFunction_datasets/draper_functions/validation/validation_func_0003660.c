get_library_and_unit_name(pIIR_Declaration decl)
{
  vector<string> result;


  string lname = get_long_name(decl);

  string str;
  unsigned int i = 1;
  while (i < lname.length() && lname[i] != ':') str += tolower(lname[i++]);
  result.push_back(str);
  i++;
  str = "";
  while (i < lname.length() && lname[i] != ':') str += tolower(lname[i++]);
  result.push_back(str);

  return result;
}
