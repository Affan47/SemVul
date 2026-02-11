IsIdentical(Filename const &fn) const
{
  std::string realpath1;
  std::string realpath2;
  Realpath(FileName.c_str(), realpath1);
  Realpath(fn.GetFileName(), realpath2);
  gdcmDebugMacro( "IsIdentical: " << realpath1 << " vs " << realpath2 );
  return realpath1 == realpath2;
}
