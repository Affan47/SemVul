gridfile_fill_buf_from_chunk(gridfile *gfile, const bson *chunk, gridfs_offset chunksize, char **buf, int *allocatedMem, char **targetBuf,
                                                  size_t *targetBufLen, gridfs_offset *bytes_left, int chunkNo){
  bson_iterator it[1];
  gridfs_offset chunk_len;
  const char *chunk_data;

  if( bson_find(it, chunk, "data") != BSON_EOO ) {
    chunk_len = bson_iterator_bin_len(it);
    chunk_data = bson_iterator_bin_data(it);
    if( gridfs_read_filter( targetBuf, targetBufLen, chunk_data, (size_t)chunk_len, gfile->flags ) != 0) return 0;
    *allocatedMem = *targetBuf != chunk_data;
    chunk_data = *targetBuf;
    if (chunkNo == 0) {
      chunk_data += (gfile->pos) % chunksize;
      *targetBufLen -= (size_t)( (gfile->pos) % chunksize );
    }
    if (*bytes_left > *targetBufLen) {
      memcpy(*buf, chunk_data, *targetBufLen);
      *bytes_left -= *targetBufLen;
      *buf += *targetBufLen;
      return *targetBufLen;
    } else {
      memcpy(*buf, chunk_data, (size_t)(*bytes_left));
      return *bytes_left;
    }
  } else {
    bson_fatal_msg( 0, "Chunk object doesn't have 'data' attribute" );
    return 0;
  }
}
