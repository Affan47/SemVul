Open( const unsigned char *pBufferBytes, size_t bufferSizeInBytes )
{

  err = FT_New_Memory_Face( *FTLibrary::GetInstance()->GetLibrary(),
                            pBufferBytes,
                            bufferSizeInBytes,
                            0,
                            &ftFace);

  if( err)
    {
    return false;
    }
    else
    {
    charMap = new FTCharmap( ftFace);
    return true;
  }
}
