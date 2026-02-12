dns_zonemgr_setsize(dns_zonemgr_t *zmgr, int num_zones) {
	isc_result_t result;
	int ntasks = num_zones / ZONES_PER_TASK;
	int nmctx = num_zones / ZONES_PER_MCTX;
	isc_taskpool_t *pool = NULL;
	isc_pool_t *mctxpool = NULL;

	REQUIRE(DNS_ZONEMGR_VALID(zmgr));


	if (ntasks < 10)
		ntasks = 10;
	if (nmctx < 2)
		nmctx = 2;


	if (zmgr->zonetasks == NULL)
		result = isc_taskpool_create(zmgr->taskmgr, zmgr->mctx,
					     ntasks, 2, &pool);
	else
		result = isc_taskpool_expand(&zmgr->zonetasks, ntasks, &pool);

	if (result == ISC_R_SUCCESS)
		zmgr->zonetasks = pool;

	pool = NULL;
	if (zmgr->loadtasks == NULL)
		result = isc_taskpool_create(zmgr->taskmgr, zmgr->mctx,
					     ntasks, 2, &pool);
	else
		result = isc_taskpool_expand(&zmgr->loadtasks, ntasks, &pool);

	if (result == ISC_R_SUCCESS)
		zmgr->loadtasks = pool;


	isc_taskpool_setprivilege(zmgr->loadtasks, true);


	if (zmgr->mctxpool == NULL)
		result = isc_pool_create(zmgr->mctx, nmctx, mctxfree,
					 mctxinit, NULL, &mctxpool);
	else
		result = isc_pool_expand(&zmgr->mctxpool, nmctx, &mctxpool);

	if (result == ISC_R_SUCCESS)
		zmgr->mctxpool = mctxpool;

	return (result);
}
