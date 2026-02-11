MetaIndexFile(const char *Type) const
{
   return _config->FindDir("Dir::State::lists") +
      URItoFileName(MetaIndexURI(Type));
}
