IndexFile(const char *Type) const
{
   string s =_config->FindDir("Dir::State::lists") + URItoFileName(IndexURI(Type));
   string sgzip = s + ".gz";
   if (!FileExists(s) && FileExists(sgzip))
       return sgzip;
   else
       return s;
}
