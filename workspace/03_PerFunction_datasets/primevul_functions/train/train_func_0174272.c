int sqlite3CodecAttach(sqlite3* db, int nDb, const void *zKey, int nKey) {
  struct Db *pDb = &db->aDb[nDb];

  CODEC_TRACE("sqlite3CodecAttach: entered db=%p, nDb=%d zKey=%s, nKey=%d\n", db, nDb, (char *)zKey, nKey);


  if(nKey && zKey && pDb->pBt) {
    int rc;
    Pager *pPager = pDb->pBt->pBt->pPager;
    sqlite3_file *fd;
    codec_ctx *ctx;


    if((fd = sqlite3PagerFile(pPager))->pMethods == 0) fd = NULL;

    CODEC_TRACE("sqlite3CodecAttach: calling sqlcipher_activate()\n");
    sqlcipher_activate();

    CODEC_TRACE_MUTEX("sqlite3CodecAttach: entering database mutex %p\n", db->mutex);
    sqlite3_mutex_enter(db->mutex);
    CODEC_TRACE_MUTEX("sqlite3CodecAttach: entered database mutex %p\n", db->mutex);

#ifdef SQLCIPHER_EXT
    if((rc = sqlite3_set_authorizer(db, sqlcipher_license_authorizer, db)) != SQLITE_OK) {
      sqlite3_mutex_leave(db->mutex);
      return rc;
    }
#endif


    CODEC_TRACE("sqlite3CodecAttach: calling sqlcipher_codec_ctx_init()\n");
    rc = sqlcipher_codec_ctx_init(&ctx, pDb, pDb->pBt->pBt->pPager, zKey, nKey);

    if(rc != SQLITE_OK) {

      CODEC_TRACE("sqlite3CodecAttach: context initialization failed with rc=%d\n", rc);


      sqlite3pager_error(pPager, rc);
      pDb->pBt->pBt->db->errCode = rc;
      CODEC_TRACE_MUTEX("sqlite3CodecAttach: leaving database mutex %p (early return on rc=%d)\n", db->mutex, rc);
      sqlite3_mutex_leave(db->mutex);
      CODEC_TRACE_MUTEX("sqlite3CodecAttach: left database mutex %p (early return on rc=%d)\n", db->mutex, rc);
      return rc;
    }

    CODEC_TRACE("sqlite3CodecAttach: calling sqlite3PagerSetCodec()\n");
    sqlite3PagerSetCodec(sqlite3BtreePager(pDb->pBt), sqlite3Codec, NULL, sqlite3FreeCodecArg, (void *) ctx);

    CODEC_TRACE("sqlite3CodecAttach: calling codec_set_btree_to_codec_pagesize()\n");
    codec_set_btree_to_codec_pagesize(db, pDb, ctx);


    CODEC_TRACE("sqlite3CodecAttach: calling sqlite3BtreeSecureDelete()\n");
    sqlite3BtreeSecureDelete(pDb->pBt, 1);


    if(fd != NULL) {
      CODEC_TRACE("sqlite3CodecAttach: calling sqlite3BtreeSetAutoVacuum()\n");
      sqlite3BtreeSetAutoVacuum(pDb->pBt, SQLITE_DEFAULT_AUTOVACUUM);
    }
    CODEC_TRACE_MUTEX("sqlite3CodecAttach: leaving database mutex %p\n", db->mutex);
    sqlite3_mutex_leave(db->mutex);
    CODEC_TRACE_MUTEX("sqlite3CodecAttach: left database mutex %p\n", db->mutex);
  }
  return SQLITE_OK;
}
