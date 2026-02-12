static CURLcode deflate_unencode_write(struct Curl_easy *data,
                                       struct contenc_writer *writer,
                                       const char *buf, size_t nbytes)
{
  struct zlib_params *zp = (struct zlib_params *) &writer->params;
  z_stream *z = &zp->z;


  z->next_in = (Bytef *) buf;
  z->avail_in = (uInt) nbytes;

  if(zp->zlib_init == ZLIB_EXTERNAL_TRAILER)
    return process_trailer(data, zp);


  return inflate_stream(data, writer, ZLIB_INFLATING);
}
