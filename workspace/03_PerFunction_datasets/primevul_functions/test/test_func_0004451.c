static CURLcode gzip_init_writer(struct Curl_easy *data,
                                 struct contenc_writer *writer)
{
  struct zlib_params *zp = (struct zlib_params *) &writer->params;
  z_stream *z = &zp->z;

  if(!writer->downstream)
    return CURLE_WRITE_ERROR;


  z->zalloc = (alloc_func) zalloc_cb;
  z->zfree = (free_func) zfree_cb;

  if(strcmp(zlibVersion(), "1.2.0.4") >= 0) {

    if(inflateInit2(z, MAX_WBITS + 32) != Z_OK) {
      return process_zlib_error(data, z);
    }
    zp->zlib_init = ZLIB_INIT_GZIP;
  }
  else {

    if(inflateInit2(z, -MAX_WBITS) != Z_OK) {
      return process_zlib_error(data, z);
    }
    zp->trailerlen = 8;
    zp->zlib_init = ZLIB_INIT;
  }

  return CURLE_OK;
}
