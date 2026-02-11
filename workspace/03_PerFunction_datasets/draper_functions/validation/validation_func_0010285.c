__ram_ca_setorder(dbc, my_dbc, foundp, pgno, order, args)
	DBC *dbc, *my_dbc;
	u_int32_t *foundp;
	db_pgno_t pgno;
	u_int32_t order;
	void *args;
{
	BTREE_CURSOR *cp, *cp_arg;
	int adjusted;
	ca_recno_arg op;
	db_recno_t recno;

	COMPQUIET(pgno, 0);

	cp = (BTREE_CURSOR *)dbc->internal;
	cp_arg = (BTREE_CURSOR *)my_dbc->internal;
	op = *(ca_recno_arg *)args;

	if (cp_arg->root != cp->root ||
	    MVCC_SKIP_CURADJ(dbc, BAM_ROOT_PGNO(dbc)))
		return (0);
	++(*foundp);
	adjusted = 0;
	recno = cp_arg->recno;
	switch (op) {
	case CA_DELETE:
		if (recno < cp->recno) {
			--cp->recno;


			if (recno == cp->recno && CD_ISSET(cp))
				cp->order += order;
		} else if (recno == cp->recno &&
		    !CD_ISSET(cp)) {
			CD_SET(cp);
			cp->order = order;


			cp->stream_start_pgno = PGNO_INVALID;
		}
		break;
	case CA_IBEFORE:


		if (C_EQUAL(cp_arg, cp)) {
			++cp->recno;
			adjusted = 1;
		}
		goto iafter;
	case CA_ICURRENT:


		DB_ASSERT(dbc->dbp->env, CD_ISSET(cp_arg));
		if (C_EQUAL(cp_arg, cp)) {
			CD_CLR(cp);
			break;
		}

	case CA_IAFTER:
iafter:		if (!adjusted && C_LESSTHAN(cp_arg, cp)) {
			++cp->recno;
			adjusted = 1;
		}
		if (recno == cp->recno && adjusted)


			cp->order -= (cp_arg->order - 1);
		break;
	}
	return (0);
}
