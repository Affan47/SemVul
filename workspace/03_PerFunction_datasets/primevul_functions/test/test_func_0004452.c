static CURLcode inflate_stream(struct Curl_easy *data,
                               struct contenc_writer *writer,
                               zlibInitState started)
{
  struct zlib_params *zp = (struct zlib_params *) &writer->params;
  z_stream *z = &zp->z;
  uInt nread = z->avail_in;
  Bytef *orig_in = z->next_in;
  bool done = FALSE;
  CURLcode result = CURLE_OK;
  char *decomp;


  if(zp->zlib_init != ZLIB_INIT &&
     zp->zlib_init != ZLIB_INFLATING &&
     zp->zlib_init != ZLIB_INIT_GZIP &&
     zp->zlib_init != ZLIB_GZIP_INFLATING)
    return exit_zlib(data, z, &zp->zlib_init, CURLE_WRITE_ERROR);


  decomp = malloc(DSIZ);
  if(!decomp)
    return exit_zlib(data, z, &zp->zlib_init, CURLE_OUT_OF_MEMORY);


  while(!done) {
    int status;
    done = TRUE;


    z->next_out = (Bytef *) decomp;
    z->avail_out = DSIZ;

#ifdef Z_BLOCK

    status = inflate(z, Z_BLOCK);
#else

    status = inflate(z, Z_SYNC_FLUSH);
#endif


    if(z->avail_out != DSIZ) {
      if(status == Z_OK || status == Z_STREAM_END) {
        zp->zlib_init = started;
        result = Curl_unencode_write(data, writer->downstream, decomp,
                                     DSIZ - z->avail_out);
        if(result) {
          exit_zlib(data, z, &zp->zlib_init, result);
          break;
        }
      }
    }


    switch(status) {
    case Z_OK:

      done = FALSE;
      break;
    case Z_BUF_ERROR:

      break;
    case Z_STREAM_END:
      result = process_trailer(data, zp);
      break;
    case Z_DATA_ERROR:


      if(zp->zlib_init == ZLIB_INIT) {

        (void) inflateEnd(z);
        if(inflateInit2(z, -MAX_WBITS) == Z_OK) {
          z->next_in = orig_in;
          z->avail_in = nread;
          zp->zlib_init = ZLIB_INFLATING;
          zp->trailerlen = 4;
          done = FALSE;
          break;
        }
        zp->zlib_init = ZLIB_UNINIT;
      }
      result = exit_zlib(data, z, &zp->zlib_init, process_zlib_error(data, z));
      break;
    default:
      result = exit_zlib(data, z, &zp->zlib_init, process_zlib_error(data, z));
      break;
    }
  }
  free(decomp);


  if(nread && zp->zlib_init == ZLIB_INIT)
    zp->zlib_init = started;

  return result;
}
