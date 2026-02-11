show_split (string s)
{
  vector<string> tmp = split_param (s);
  cerr << "Splitting <" << s << ">: ";
  for (uint i = 0; i < tmp.size(); i ++)
    cerr << "<" << tmp[i] << ">, ";
  cerr << "\n";
}
