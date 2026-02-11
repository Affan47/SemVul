__rep_bt_cmp(dbp, dbt1, dbt2, locp)
	DB *dbp;
	const DBT *dbt1, *dbt2;
	size_t *locp;
{
	DB_LSN lsn1, lsn2;
	__rep_control_args *rp1, *rp2;

	COMPQUIET(dbp, NULL);
	COMPQUIET(locp, NULL);

	rp1 = dbt1->data;
	rp2 = dbt2->data;

	(void)__ua_memcpy(&lsn1, &rp1->lsn, sizeof(DB_LSN));
	(void)__ua_memcpy(&lsn2, &rp2->lsn, sizeof(DB_LSN));

	if (lsn1.file > lsn2.file)
		return (1);

	if (lsn1.file < lsn2.file)
		return (-1);

	if (lsn1.offset > lsn2.offset)
		return (1);

	if (lsn1.offset < lsn2.offset)
		return (-1);

	return (0);
}
