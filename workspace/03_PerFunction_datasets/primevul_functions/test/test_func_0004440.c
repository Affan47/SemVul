static CURLcode gzip_unencode_write(struct Curl_easy *data,
                                    struct contenc_writer *writer,
                                    const char *buf, size_t nbytes)
{
  struct zlib_params *zp = (struct zlib_params *) &writer->params;
  z_stream *z = &zp->z;

  if(zp->zlib_init == ZLIB_INIT_GZIP) {

    z->next_in = (Bytef *) buf;
    z->avail_in = (uInt) nbytes;

    return inflate_stream(data, writer, ZLIB_INIT_GZIP);
  }

#ifndef OLD_ZLIB_SUPPORT


  return exit_zlib(data, z, &zp->zlib_init, CURLE_WRITE_ERROR);

#else


  switch(zp->zlib_init) {

  case ZLIB_INIT:
  {

    ssize_t hlen;

    switch(check_gzip_header((unsigned char *) buf, nbytes, &hlen)) {
    case GZIP_OK:
      z->next_in = (Bytef *) buf + hlen;
      z->avail_in = (uInt) (nbytes - hlen);
      zp->zlib_init = ZLIB_GZIP_INFLATING;
      break;

    case GZIP_UNDERFLOW:


      z->avail_in = (uInt) nbytes;
      z->next_in = malloc(z->avail_in);
      if(!z->next_in) {
        return exit_zlib(data, z, &zp->zlib_init, CURLE_OUT_OF_MEMORY);
      }
      memcpy(z->next_in, buf, z->avail_in);
      zp->zlib_init = ZLIB_GZIP_HEADER;

      return CURLE_OK;

    case GZIP_BAD:
    default:
      return exit_zlib(data, z, &zp->zlib_init, process_zlib_error(data, z));
    }

  }
  break;

  case ZLIB_GZIP_HEADER:
  {

    ssize_t hlen;
    z->avail_in += (uInt) nbytes;
    z->next_in = Curl_saferealloc(z->next_in, z->avail_in);
    if(!z->next_in) {
      return exit_zlib(data, z, &zp->zlib_init, CURLE_OUT_OF_MEMORY);
    }

    memcpy(z->next_in + z->avail_in - nbytes, buf, nbytes);

    switch(check_gzip_header(z->next_in, z->avail_in, &hlen)) {
    case GZIP_OK:

      free(z->next_in);

      z->next_in = (Bytef *) buf + hlen + nbytes - z->avail_in;
      z->avail_in = (uInt) (z->avail_in - hlen);
      zp->zlib_init = ZLIB_GZIP_INFLATING;
      break;

    case GZIP_UNDERFLOW:

      return CURLE_OK;

    case GZIP_BAD:
    default:
      return exit_zlib(data, z, &zp->zlib_init, process_zlib_error(data, z));
    }

  }
  break;

  case ZLIB_EXTERNAL_TRAILER:
    z->next_in = (Bytef *) buf;
    z->avail_in = (uInt) nbytes;
    return process_trailer(data, zp);

  case ZLIB_GZIP_INFLATING:
  default:

    z->next_in = (Bytef *) buf;
    z->avail_in = (uInt) nbytes;
    break;
  }

  if(z->avail_in == 0) {

    return CURLE_OK;
  }


  return inflate_stream(data, writer, ZLIB_GZIP_INFLATING);
#endif
}
