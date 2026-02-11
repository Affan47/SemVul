compute_terminate()
{

	if (NULL != compute_evaluators_lock) {
		compute_evaluator *current = compute_evaluators;
		slapi_rwlock_wrlock(compute_evaluators_lock);
		while (current != NULL) {
			compute_evaluator *asabird = current;
			current = current->next;
			slapi_ch_free((void **)&asabird);
		}
		slapi_rwlock_unlock(compute_evaluators_lock);

		slapi_destroy_rwlock(compute_evaluators_lock);
	}
	if (NULL != compute_rewriters_lock) {
		compute_rewriter *current = compute_rewriters;
		slapi_rwlock_wrlock(compute_rewriters_lock);
		while (current != NULL) {
			compute_rewriter *asabird = current;
			current = current->next;
			slapi_ch_free((void **)&asabird);
		}
		slapi_rwlock_unlock(compute_rewriters_lock);
		slapi_destroy_rwlock(compute_rewriters_lock);
	}
	return 0;
}
