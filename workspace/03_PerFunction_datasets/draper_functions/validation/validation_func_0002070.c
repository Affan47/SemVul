RTMP_SendChunk(RTMP *r, RTMPChunk *chunk)
{
  bool wrote;
  char hbuf[RTMP_MAX_HEADER_SIZE];

  Log(LOGDEBUG2, "%s: fd=%d, size=%d", __FUNCTION__, r->m_socket, chunk->c_chunkSize);
  LogHexString(LOGDEBUG2, chunk->c_header, chunk->c_headerSize);
  if (chunk->c_chunkSize)
    {
      char *ptr = chunk->c_chunk - chunk->c_headerSize;
      LogHexString(LOGDEBUG2, chunk->c_chunk, chunk->c_chunkSize);

      memcpy(hbuf, ptr, chunk->c_headerSize);
      memcpy(ptr, chunk->c_header, chunk->c_headerSize);
      wrote = WriteN(r, ptr, chunk->c_headerSize + chunk->c_chunkSize);
      memcpy(ptr, hbuf, chunk->c_headerSize);
    }
  else
    wrote = WriteN(r, chunk->c_header, chunk->c_headerSize);
  return wrote;
}
