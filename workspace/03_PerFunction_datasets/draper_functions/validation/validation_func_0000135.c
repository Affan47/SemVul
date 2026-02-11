file_fillBuffer ()
{
  int bytesread = 0;
  int n = FILE_MAXLEN - file_ptr;

  int bytestoread = file_ptr;

  if (file_ptr < FILE_MAXLEN)
    if (file_buffer [file_ptr] == 0)
      return 0;

  if (file_ptr <= FILE_MAXLEN / 2) return 1;

  memcpy (file_buffer, &file_buffer [file_ptr], n);

  if (file_reverse)
  {
    if (file_bufferstart - bytestoread - file_bufferread >= 0)
    {
      fseek (file_file, -bytestoread - file_bufferread, SEEK_CUR);
      file_bufferstart += -bytestoread - file_bufferread;
    }
    else
    {
      bytestoread = (int) file_bufferstart - file_bufferread;
      fseek (file_file, 0, SEEK_SET);
      file_bufferstart = 0;
      memset (&file_buffer [n + bytestoread], 0, FILE_MAXLEN - (n + bytestoread));
    }
  }

  bytesread = fread (&file_buffer [n], 1, bytestoread, file_file);
  file_bufferlen = file_bufferlen + bytesread - file_ptr;
  file_bufferread = bytesread;

  file_bufferstart += bytesread;
  if (file_reverse)
  {
    if (bytesread > 0)
      file_revertBuffer (n, n + bytesread - 1);
  }

  if (bytesread != file_ptr)
  {
    if (file_bufferlen >= 0 && file_bufferlen < FILE_MAXLEN)
      file_buffer [file_bufferlen] = 0;
  }
  file_ptr = 0;
  return 1;
}
