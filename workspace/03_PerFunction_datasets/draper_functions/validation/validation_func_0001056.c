Custom600Headers()
{
   string Final = _config->FindDir("Dir::State::lists");
   Final += URItoFileName(RealURI);

   struct stat Buf;
   if (stat(Final.c_str(),&Buf) != 0)
   {
      Final = DestFile + ".reverify";
      if (stat(Final.c_str(),&Buf) != 0)
	 return "\nIndex-File: true\nFail-Ignore: true\n";
   }

   return "\nIndex-File: true\nFail-Ignore: true\nLast-Modified: " + TimeRFC1123(Buf.st_mtime);
}
