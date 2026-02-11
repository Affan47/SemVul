main(int argc, char* argv[])
{
  GdomeString hello("hello");
  std::cout << hello << std::endl;

  Document doc;
  UTF8String utf8_hi = hello;
  UCS4String ucs4_hi = hello;

  std::string c_hi1 = utf8_hi;

  if (doc) ;
  if (!doc) ;
  if (doc == 0) ;
  if (doc != 0) ;

  GdomeString ns;
  if (ns) std::cout << "WARNING: GdomeString: null != null" << std::endl;
  if (!ns) std::cout << "OK: GdomeString: null == null" << std::endl;

  return 0;
}
