qpol_syn_terule_get_lineno(const qpol_policy_t * policy, const qpol_syn_terule_t * rule, unsigned long *lineno)
{
	avrule_t *internal_rule = NULL;

	if (lineno)
		*lineno = 0;

	if (!policy || !rule || !lineno) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_rule = ((struct qpol_syn_rule *)rule)->rule;

	*lineno = internal_rule->line;

	return STATUS_SUCCESS;
}
