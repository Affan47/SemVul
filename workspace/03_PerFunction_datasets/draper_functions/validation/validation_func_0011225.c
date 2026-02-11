__clear_fe_watermark(txn, db)
     DB_TXN *txn;
     DB *db;
{
	MPOOLFILE *mpf;

	mpf = db->mpf->mfp;
	mpf->fe_watermark = PGNO_INVALID;
	mpf->fe_txnid = 0U;
	mpf->fe_nlws = 0U;
	TAILQ_REMOVE(&txn->femfs, db, felink);
}
