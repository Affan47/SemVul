AppendFrameEncode( std::ostream & out, const char * data, size_t datalen )
{
  const unsigned int * dimensions = this->GetDimensions();
  const PixelFormat & pf = this->GetPixelFormat(); (void)pf;
  assert( datalen == dimensions[0] * dimensions[1] * pf.GetPixelSize() );

  std::vector<BYTE> rgbyteCompressed;
  rgbyteCompressed.resize(dimensions[0] * dimensions[1] * 4);

  size_t cbyteCompressed;
  const bool b = this->CodeFrameIntoBuffer((char*)&rgbyteCompressed[0], rgbyteCompressed.size(), cbyteCompressed, data, datalen );
  if( !b ) return false;

  out.write( (char*)&rgbyteCompressed[0], cbyteCompressed );

  return true;
}
