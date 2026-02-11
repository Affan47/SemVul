gabufr_load2mem(const char * path, gabufr_dset * dset) {
  off_t bytesread, bytesleft, filesize;
  FILE * datafile;
  unsigned char * filebuf;
  unsigned char * pos;

  if ((datafile = fopen(path, "r")) == NULL) {
      printf("Can't open BUFR file %s: %s\n", path, strerror(errno));
      return GABUFR_ERR;
  }

  fseeko(datafile, 0, SEEK_END);
  bytesleft = filesize = ftello(datafile);
  fseeko(datafile, 0, SEEK_SET);
  if (GABUFR_DEBUG) printf("filesize is %ld\n", filesize);

  pos = filebuf = malloc(filesize);
  if (filebuf == NULL) {
    printf("Couldn't allocate memory for file parsing\n");
    return GABUFR_ERR;
  }

  while (bytesleft > 0) {
    bytesread = fread(pos, 1, bytesleft, datafile);
    if (GABUFR_DEBUG) printf("read %ld bytes\n", bytesleft);
    if (ferror(datafile)) {
      printf("Low level read error on BUFR file %s\n", path);
      free(filebuf);
      fclose(datafile);
      return GABUFR_ERR;
    }

    if (feof(datafile) && bytesleft) {
      if (GABUFR_DEBUG) printf("Ran out of data in BUFR file %s!\n", path);
      free(filebuf);
      fclose(datafile);
      return GABUFR_ERR;
    }

    bytesleft -= bytesread;
    pos += bytesread;
  }
  fclose(datafile);
  dset->buf = filebuf;
  dset->len = filesize;
  dset->msgs = NULL;
  return GABUFR_OK;
}
