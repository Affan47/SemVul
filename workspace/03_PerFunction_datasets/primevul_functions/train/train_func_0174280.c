static void* sqlite3Codec(void *iCtx, void *data, Pgno pgno, int mode) {
  codec_ctx *ctx = (codec_ctx *) iCtx;
  int offset = 0, rc = 0;
  int page_sz = sqlcipher_codec_ctx_get_pagesize(ctx);
  unsigned char *pData = (unsigned char *) data;
  void *buffer = sqlcipher_codec_ctx_get_data(ctx);
  int plaintext_header_sz = sqlcipher_codec_ctx_get_plaintext_header_size(ctx);
  int cctx = CIPHER_READ_CTX;

  CODEC_TRACE("sqlite3Codec: entered pgno=%d, mode=%d, page_sz=%d\n", pgno, mode, page_sz);

#ifdef SQLCIPHER_EXT
  if(sqlcipher_license_check(ctx) != SQLITE_OK) return NULL;
#endif


  if((rc = sqlcipher_codec_key_derive(ctx)) != SQLITE_OK) {
   sqlcipher_codec_ctx_set_error(ctx, rc);
   return NULL;
  }


  if(plaintext_header_sz < 0) {
    sqlcipher_codec_ctx_set_error(ctx, SQLITE_ERROR);
    return NULL;
  }

  if(pgno == 1)
    offset = plaintext_header_sz ? plaintext_header_sz : FILE_HEADER_SZ;


  CODEC_TRACE("sqlite3Codec: switch mode=%d offset=%d\n",  mode, offset);
  switch(mode) {
    case CODEC_READ_OP:
      if(pgno == 1)
        memcpy(buffer, plaintext_header_sz ? pData : (void *) SQLITE_FILE_HEADER, offset);

      rc = sqlcipher_page_cipher(ctx, cctx, pgno, CIPHER_DECRYPT, page_sz - offset, pData + offset, (unsigned char*)buffer + offset);
#ifdef SQLCIPHER_TEST
      if(cipher_fail_next_decrypt) rc = SQLITE_ERROR;
#endif
      if(rc != SQLITE_OK) {
        sqlcipher_memset((unsigned char*) buffer+offset, 0, page_sz-offset);
        sqlcipher_codec_ctx_set_error(ctx, rc);
      }
      memcpy(pData, buffer, page_sz);
      return pData;
      break;

    case CODEC_WRITE_OP:
      cctx = CIPHER_WRITE_CTX;

    case CODEC_JOURNAL_OP:
      if(pgno == 1) {
        void *kdf_salt = NULL;

        if((rc = sqlcipher_codec_ctx_get_kdf_salt(ctx, &kdf_salt)) != SQLITE_OK) {
          sqlcipher_codec_ctx_set_error(ctx, rc);
          return NULL;
        }
        memcpy(buffer, plaintext_header_sz ? pData : kdf_salt, offset);
      }
      rc = sqlcipher_page_cipher(ctx, cctx, pgno, CIPHER_ENCRYPT, page_sz - offset, pData + offset, (unsigned char*)buffer + offset);
#ifdef SQLCIPHER_TEST
      if(cipher_fail_next_encrypt) rc = SQLITE_ERROR;
#endif
      if(rc != SQLITE_OK) {
        sqlcipher_memset((unsigned char*)buffer+offset, 0, page_sz-offset);
        sqlcipher_codec_ctx_set_error(ctx, rc);
        return NULL;
      }
      return buffer;
      break;

    default:
      sqlcipher_codec_ctx_set_error(ctx, SQLITE_ERROR);
      return pData;
      break;
  }
}
