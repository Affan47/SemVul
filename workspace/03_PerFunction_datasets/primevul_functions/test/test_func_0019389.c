static size_t my_fwrite(void *buffer, size_t sz, size_t nmemb, void *stream)
{
  size_t rc;
  struct OutStruct *out=(struct OutStruct *)stream;
  struct Configurable *config = out->config;

  if(!out->stream) {

    out->stream=fopen(out->filename, "wb");
    if(!out->stream) {
      warnf(config, "Failed to create the file %s\n", out->filename);


      rc = (0 == (sz * nmemb)) ? 1 : 0;
      return rc;
    }
  }

  rc = fwrite(buffer, sz, nmemb, out->stream);

  if((sz * nmemb) == rc) {

    out->bytes += (sz * nmemb);
  }

  if(config->nobuffer)

    fflush(out->stream);

  return rc;
}
