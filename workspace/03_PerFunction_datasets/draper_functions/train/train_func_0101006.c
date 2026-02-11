isns_scope_get(isns_scope_t *scope)
{
	if (scope) {
		isns_assert(scope->ic_users);
		scope->ic_users++;
	}
	return scope;
}
