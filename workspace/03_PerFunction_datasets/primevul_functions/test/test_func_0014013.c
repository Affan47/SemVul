booleanMatch(
	int *matchp,
	slap_mask_t flags,
	Syntax *syntax,
	MatchingRule *mr,
	struct berval *value,
	void *assertedValue )
{

	struct berval *asserted = (struct berval *) assertedValue;
	*matchp = (int) asserted->bv_len - (int) value->bv_len;
	return LDAP_SUCCESS;
}
