seek(long offset, int whence, bool nothrow)
{
  int nwhere = 0;
  switch (whence)
    {
    case SEEK_SET: nwhere = 0; break;
    case SEEK_CUR: nwhere = where; break;
    case SEEK_END: nwhere = bsize; break;
    default: G_THROW("bad_arg\tByteStream::Static::seek()");
    }
  nwhere += offset;
  if (nwhere<0)
    G_THROW( ERR_MSG("ByteStream.seek_error2") );
  where = nwhere;
  return 0;
}
