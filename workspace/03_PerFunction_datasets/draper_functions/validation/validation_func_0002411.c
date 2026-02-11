test_get_filter_info(void)
{
  unsigned int flags;
  herr_t err;

  TESTING("H5Zget_filter_info");


#ifdef H5_HAVE_FILTER_FLETCHER32
  if(H5Zget_filter_info(H5Z_FILTER_FLETCHER32, &flags) < 0) TEST_ERROR

  if(((flags & H5Z_FILTER_CONFIG_ENCODE_ENABLED) == 0) ||
     ((flags & H5Z_FILTER_CONFIG_DECODE_ENABLED) == 0))
      TEST_ERROR
#endif

#ifdef H5_HAVE_FILTER_SHUFFLE
  if(H5Zget_filter_info(H5Z_FILTER_SHUFFLE, &flags) < 0) TEST_ERROR

  if(((flags & H5Z_FILTER_CONFIG_ENCODE_ENABLED) == 0) ||
     ((flags & H5Z_FILTER_CONFIG_DECODE_ENABLED) == 0))
      TEST_ERROR
#endif

#ifdef H5_HAVE_FILTER_DEFLATE
  if(H5Zget_filter_info(H5Z_FILTER_DEFLATE, &flags) < 0) TEST_ERROR

  if(((flags & H5Z_FILTER_CONFIG_ENCODE_ENABLED) == 0) ||
     ((flags & H5Z_FILTER_CONFIG_DECODE_ENABLED) == 0))
      TEST_ERROR
#endif

#ifdef H5_HAVE_FILTER_SZIP
    if(H5Zget_filter_info(H5Z_FILTER_SZIP, &flags) < 0) TEST_ERROR

    if(SZ_encoder_enabled()) {
        if(((flags & H5Z_FILTER_CONFIG_ENCODE_ENABLED) == 0) ||
                ((flags & H5Z_FILTER_CONFIG_DECODE_ENABLED) == 0))
            TEST_ERROR
    }
    else {
        if(((flags & H5Z_FILTER_CONFIG_ENCODE_ENABLED) != 0) ||
                ((flags & H5Z_FILTER_CONFIG_DECODE_ENABLED) == 0))
            TEST_ERROR
    }
#endif


  H5E_BEGIN_TRY {
    err = H5Zget_filter_info(-1, &flags);
  } H5E_END_TRY;
  if(err >= 0) TEST_ERROR

  PASSED();
  return 0;

error:
  return -1;
}
