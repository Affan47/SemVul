tio_close(TFILE *fp)
{
  int retv;

  retv=tio_flush(fp);
#ifdef DEBUG_TIO_STATS

  fprintf(stderr,"DEBUG_TIO_STATS READ=%d WRITTEN=%d\n",fp->bytesread,fp->byteswritten);
#endif

  if (close(fp->fd))
    retv=-1;

  free(fp->readbuffer.buffer);
  free(fp->writebuffer.buffer);

  free(fp);

  return retv;
}
