omapi_wait_for_completion (omapi_object_t *object,
					struct timeval *t)
{
	isc_result_t status;
	omapi_waiter_object_t *waiter;
	omapi_object_t *inner;

	if (object) {
		waiter = (omapi_waiter_object_t *)0;
		status = omapi_waiter_allocate (&waiter, MDL);
		if (status != ISC_R_SUCCESS)
			return status;


		for (inner = object; inner -> inner; inner = inner -> inner)
			;

		status = omapi_object_reference (&waiter -> outer, inner, MDL);
		if (status != ISC_R_SUCCESS) {
			omapi_waiter_dereference (&waiter, MDL);
			return status;
		}

		status = omapi_object_reference (&inner -> inner,
						 (omapi_object_t *)waiter,
						 MDL);
		if (status != ISC_R_SUCCESS) {
			omapi_waiter_dereference (&waiter, MDL);
			return status;
		}
	} else
		waiter = (omapi_waiter_object_t *)0;

	do {
		status = omapi_one_dispatch ((omapi_object_t *)waiter, t);
		if (status != ISC_R_SUCCESS)
			return status;
	} while (!waiter || !waiter -> ready);

	if (waiter -> outer) {
		if (waiter -> outer -> inner) {
			omapi_object_dereference (&waiter -> outer -> inner,
						  MDL);
			if (waiter -> inner)
				omapi_object_reference
					(&waiter -> outer -> inner,
					 waiter -> inner, MDL);
		}
		omapi_object_dereference (&waiter -> outer, MDL);
	}
	if (waiter -> inner)
		omapi_object_dereference (&waiter -> inner, MDL);

	status = waiter -> waitstatus;
	omapi_waiter_dereference (&waiter, MDL);
	return status;
}
