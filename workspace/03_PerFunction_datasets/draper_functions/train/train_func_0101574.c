os_cond_broadcast(

	os_cond_t*	cond)
{
	ut_a(cond);

#ifdef __WIN__
	ut_a(wake_all_condition_variable != NULL);
	wake_all_condition_variable(cond);
#else
	ut_a(pthread_cond_broadcast(cond) == 0);
#endif
}
