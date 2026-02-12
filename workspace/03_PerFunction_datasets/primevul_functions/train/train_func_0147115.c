check_retry_cpuset(int cpuset_mems_cookie, struct alloc_context *ac)
{


	if (cpusets_enabled() && ac->nodemask &&
			!cpuset_nodemask_valid_mems_allowed(ac->nodemask)) {
		ac->nodemask = NULL;
		return true;
	}


	if (read_mems_allowed_retry(cpuset_mems_cookie))
		return true;

	return false;
}
