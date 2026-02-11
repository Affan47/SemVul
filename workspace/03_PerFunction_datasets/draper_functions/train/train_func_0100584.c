starts_with_utf8_bom(const Blob *pContent, int *pnByte){
  const char *z = blob_buffer(pContent);
  int bomSize = 0;
  const unsigned char *bom = get_utf8_bom(&bomSize);

  if( pnByte ) *pnByte = bomSize;
  if( blob_size(pContent)<bomSize ) return 0;
  return memcmp(z, bom, bomSize)==0;
}
