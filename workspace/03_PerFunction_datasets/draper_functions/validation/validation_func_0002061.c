SetOverlay(const char *array, unsigned int length)
{
  if( !array || length == 0 ) return;

  unsigned int computed_length = (Internal->Rows * Internal->Columns + 7) / 8;
  Internal->Data.resize( computed_length );
  if( length < computed_length )
    {
    gdcmWarningMacro( "Not enough data found in Overlay. Proceed with caution" );
    std::copy(array, array+length, Internal->Data.begin());
    }
  else
    {
    if( length > computed_length )
      {
      gdcmWarningMacro( "Too much data found in Overlay. Discarding extra data: " << (length - computed_length) << " bytes." );
      }

    std::copy(array, array+computed_length, Internal->Data.begin());
    }


  assert( Internal->Data.size() == computed_length );
}
