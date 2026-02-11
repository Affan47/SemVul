pg_db_lo_import (SV * dbh, char * filename)
{

	Oid loid;
	dTHX;
	D_imp_dbh(dbh);

	if (TSTART_slow) TRC(DBILOGFP, "%sBegin pg_db_lo_import (filename: %s)\n", THEADER_slow, filename);

	if (!pg_db_start_txn(aTHX_ dbh,imp_dbh))
		return 0;

	if (TLIBPQ_slow) {
		TRC(DBILOGFP, "%slo_import\n", THEADER_slow);
	}
	loid = lo_import(imp_dbh->conn, filename);

	if (DBIc_has(imp_dbh, DBIcf_AutoCommit)) {
		if (!pg_db_end_txn(aTHX_ dbh, imp_dbh, 0==loid ? 0 : 1))
			return 0;
	}

	return loid;

}
