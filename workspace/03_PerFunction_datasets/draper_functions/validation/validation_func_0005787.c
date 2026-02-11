Verify(const File& file) const
{
  MediaStorage ms;
  ms.SetFromFile(file);

  const IODs &iods = GetIODs();
  const Modules &modules = GetModules();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented" );
    return false;
    }
  const IOD &iod = iods.GetIOD( iodname );


  size_t niods = iod.GetNumberOfIODs();
  bool v = true;

  for(size_t idx = 0; idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();
    Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );

    v = v && module.Verify( file.GetDataSet(), ut );
    }

  return v;

}
