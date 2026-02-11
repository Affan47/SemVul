dbsetnull(DBPROCESS * dbproc, int bindtype, int bindlen, BYTE *bindval)
{
	BYTE *pval;

	tdsdump_log(TDS_DBG_FUNC, "dbsetnull(%p, %d, %d, %p)\n", dbproc, bindtype, bindlen, bindval);

	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_PARAMETER(bindval, SYBENBVP, FAIL);

	switch (bindtype) {
	case DATETIMEBIND:
	case DECIMALBIND:
	case FLT8BIND:
	case INTBIND:
	case MONEYBIND:
	case NUMERICBIND:
	case REALBIND:
	case SMALLBIND:
	case SMALLDATETIMEBIND:
	case SMALLMONEYBIND:
	case TINYBIND:
	case BIGINTBIND:
		bindlen = (int)default_null_representations[bindtype].len;
		break;

	case CHARBIND:
	case BINARYBIND:
		CHECK_PARAMETER(bindlen >= 0, SYBEBBL, FAIL);
		break;

	case NTBSTRINGBIND:	bindlen = (int)strlen((char *) bindval);
		break;
	case STRINGBIND:	bindlen = (int)strlen((char *) bindval);
		break;
	case VARYBINBIND:	bindlen = ((TDS_VARBINARY*) bindval)->len;
		break;
	case VARYCHARBIND:	bindlen = ((TDS_VARCHAR*) bindval)->len;
		break;

#if 0
	case SENSITIVITYBIND:
	case BOUNDARYBIND:
#endif
	default:
		dbperror(dbproc, SYBEBTYP, 0);
		return FAIL;
	}

	if ((pval = malloc(bindlen)) == NULL) {
		dbperror(dbproc, SYBEMEM, errno);
		return FAIL;
	}


	if (dbproc->nullreps[bindtype].bindval != default_null_representations[bindtype].bindval)
		free((BYTE*)dbproc->nullreps[bindtype].bindval);

	memcpy(pval, bindval, bindlen);

	dbproc->nullreps[bindtype].bindval = pval;
	dbproc->nullreps[bindtype].len = bindlen;

	tdsdump_dump_buf(TDS_DBG_NETWORK, "null representation set ", pval,  bindlen);
	return SUCCEED;
}
