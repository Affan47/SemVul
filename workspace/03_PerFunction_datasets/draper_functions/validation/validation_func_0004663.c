Print(const std::string fname) const
{
  if (!fname.length()) cout << endl << *mp << endl;
  else write_ascii_matrix(fname,*mp);
}
