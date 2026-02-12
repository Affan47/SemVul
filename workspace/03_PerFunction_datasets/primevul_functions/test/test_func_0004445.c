static CURLcode process_trailer(struct Curl_easy *data,
                                struct zlib_params *zp)
{
  z_stream *z = &zp->z;
  CURLcode result = CURLE_OK;
  uInt len = z->avail_in < zp->trailerlen? z->avail_in: zp->trailerlen;


  zp->trailerlen -= len;
  z->avail_in -= len;
  z->next_in += len;
  if(z->avail_in)
    result = CURLE_WRITE_ERROR;
  if(result || !zp->trailerlen)
    result = exit_zlib(data, z, &zp->zlib_init, result);
  else {

    zp->zlib_init = ZLIB_EXTERNAL_TRAILER;
  }
  return result;
}
