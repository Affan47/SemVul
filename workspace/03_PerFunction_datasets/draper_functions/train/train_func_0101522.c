mio_file_get_fp (MIO *mio)
{
  FILE *fp = NULL;

  if (mio->type == MIO_TYPE_FILE) {
    fp = mio->impl.file.fp;
  }

  return fp;
}
