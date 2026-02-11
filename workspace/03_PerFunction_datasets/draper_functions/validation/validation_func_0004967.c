GetDecodeLength( const char *src, size_t slen )
{
  const std::string & ret = base64_decode( std::string( src, slen) );
  return ret.size();
}
