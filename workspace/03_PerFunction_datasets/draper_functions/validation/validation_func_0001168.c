apol_types_relation_access_append(const apol_policy_t * p, const apol_types_relation_access_t * a,
					     apol_vector_t * access)
{
	apol_types_relation_access_t *new_a;
	int retval = -1;
	if ((new_a = calloc(1, sizeof(*new_a))) == NULL
	    || (new_a->rules = apol_vector_create_from_vector(a->rules, NULL, NULL, NULL)) == NULL) {
		ERR(p, "%s", strerror(errno));
		goto cleanup;
	}
	new_a->type = a->type;
	if (apol_vector_append(access, new_a) < 0) {
		ERR(p, "%s", strerror(ENOMEM));
		goto cleanup;
	}
	retval = 0;
      cleanup:
	if (retval != 0) {
		apol_types_relation_access_free(new_a);
	}
	return retval;
}
