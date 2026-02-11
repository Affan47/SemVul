pg_db_pg_notifies (SV * dbh, imp_dbh_t * imp_dbh)
{
	dTHX;
	int        status;
	PGnotify * notify;
	AV *       ret;
	SV *       retsv;

	if (TSTART_slow) TRC(DBILOGFP, "%sBegin pg_db_pg_notifies\n", THEADER_slow);

	TRACE_PQCONSUMEINPUT;
	status = PQconsumeInput(imp_dbh->conn);
	if (0 == status) {
		TRACE_PQERRORMESSAGE;
		pg_error(aTHX_ dbh, PGRES_FATAL_ERROR, PQerrorMessage(imp_dbh->conn));
		if (TEND_slow) TRC(DBILOGFP, "%sEnd pg_db_pg_notifies (error)\n", THEADER_slow);
		return &PL_sv_undef;
	}

	TRACE_PQNOTIFIES;
	notify = PQnotifies(imp_dbh->conn);

	if (!notify) {
		if (TEND_slow) TRC(DBILOGFP, "%sEnd pg_db_pg_notifies (undef)\n", THEADER_slow);
		return &PL_sv_undef;
	}

	ret=newAV();
	av_push(ret, newSVpv(notify->relname,0) );
	av_push(ret, newSViv(notify->be_pid) );
	av_push(ret, newSVpv(notify->extra,0) );


	TRACE_PQFREEMEM;
 	PQfreemem(notify);

	retsv = newRV_inc(sv_2mortal((SV*)ret));

	if (TEND_slow) TRC(DBILOGFP, "%sEnd pg_db_pg_notifies\n", THEADER_slow);
	return sv_2mortal(retsv);

}
