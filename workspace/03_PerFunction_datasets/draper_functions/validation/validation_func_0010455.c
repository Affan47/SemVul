qpol_policy_match_system(qpol_policy_t * policy)
{
	int kernvers = security_policyvers();
	int currentvers = policy->p->p.policyvers;
	int error;
	if (kernvers < 0) {
		error = errno;
		ERR(policy, "%s", "Could not determine running system's policy version.");
		errno = error;
		return -1;
	}
	if (policy->p->p.policyvers > kernvers) {
		if (sepol_policydb_set_vers(policy->p, kernvers)) {
			error = errno;
			ERR(policy, "Could not downgrade policy to version %d.", kernvers);
			errno = error;
			return -1;
		}
		WARN(policy, "Policy would be downgraded from version %d to %d.", currentvers, kernvers);
	}
	return 0;
}
