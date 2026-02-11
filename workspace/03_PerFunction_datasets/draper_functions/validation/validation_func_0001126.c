__db_log_page(dbp, txn, lsn, pgno, page)
	DB *dbp;
	DB_TXN *txn;
	DB_LSN *lsn;
	db_pgno_t pgno;
	PAGE *page;
{
	DBT page_dbt;
	DB_LSN new_lsn;
	int ret;

	if (!LOGGING_ON(dbp->env) || txn == NULL)
		return (0);

	memset(&page_dbt, 0, sizeof(page_dbt));
	page_dbt.size = dbp->pgsize;
	page_dbt.data = page;

	ret = __crdel_metasub_log(dbp, txn, &new_lsn, F_ISSET(dbp,
	    DB_AM_NOT_DURABLE) ? DB_LOG_NOT_DURABLE : 0, pgno, &page_dbt, lsn);

	if (ret == 0)
		page->lsn = new_lsn;
	return (ret);
}
