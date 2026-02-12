ns_clientmgr_destroy(ns_clientmgr_t **managerp) {
	isc_result_t result;
	ns_clientmgr_t *manager;
	bool unlock = false;

	REQUIRE(managerp != NULL);
	manager = *managerp;
	*managerp = NULL;
	REQUIRE(VALID_MANAGER(manager));

	MTRACE("destroy");


	result = isc_task_beginexclusive(manager->excl);
	if (result == ISC_R_SUCCESS) {
		unlock = true;
	}

	manager->exiting = true;

	if (unlock) {
		isc_task_endexclusive(manager->excl);
	}

	if (isc_refcount_decrement(&manager->references) == 1) {
		clientmgr_destroy(manager);
	}
}
