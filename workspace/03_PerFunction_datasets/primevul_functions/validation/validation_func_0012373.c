if(pThis->pqParent == NULL) {

		pthread_mutex_destroy(pThis->mut);
		free(pThis->mut);
	}
