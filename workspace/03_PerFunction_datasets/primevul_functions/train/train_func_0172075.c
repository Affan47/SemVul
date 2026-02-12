pam_putenv(pam_handle_t *pamh, const char *name_value)
{
	int		error = PAM_SYSTEM_ERR;
	char		*equal_sign = 0;
	char		*name = NULL, *value = NULL, *tmp_value = NULL;
	env_list	*traverse, *trail;

	pam_trace(PAM_DEBUG_DEFAULT,
	    "pam_putenv(%p, %s)", (void *)pamh,
	    name_value ? name_value : "NULL");

	if (pamh == NULL || name_value == NULL)
		goto out;


	if ((equal_sign = strchr(name_value, '=')) != 0) {
		if ((name = calloc(equal_sign - name_value + 1,
		    sizeof (char))) == 0) {
			error = PAM_BUF_ERR;
			goto out;
		}
		(void) strncpy(name, name_value, equal_sign - name_value);
		if ((value = strdup(++equal_sign)) == 0) {
			error = PAM_BUF_ERR;
			goto out;
		}
	} else {
		if ((name = strdup(name_value)) == 0) {
			error = PAM_BUF_ERR;
			goto out;
		}
	}


	traverse = pamh->pam_env;
	trail = traverse;
	while (traverse && strncmp(traverse->name, name, strlen(name))) {
		trail = traverse;
		traverse = traverse->next;
	}

	if (traverse) {

		if (value == 0) {

			if (pamh->pam_env == traverse)
				pamh->pam_env = traverse->next;
			else
				trail->next = traverse->next;
			free_env(traverse);
		} else if (strlen(value) == 0) {

			if ((tmp_value = strdup("")) == 0) {
				error = PAM_SYSTEM_ERR;
				goto out;
			}
			free(traverse->value);
			traverse->value = tmp_value;
		} else {

			if ((tmp_value = strdup(value)) == 0) {
				error = PAM_SYSTEM_ERR;
				goto out;
			}
			free(traverse->value);
			traverse->value = tmp_value;
		}

	} else if (traverse == 0 && value) {


		if ((traverse = calloc(1, sizeof (env_list))) == 0) {
			error = PAM_BUF_ERR;
			goto out;
		}
		if ((traverse->name = strdup(name)) == 0) {
			free_env(traverse);
			error = PAM_BUF_ERR;
			goto out;
		}
		if ((traverse->value = strdup(value)) == 0) {
			free_env(traverse);
			error = PAM_BUF_ERR;
			goto out;
		}
		if (trail == 0) {

			pamh->pam_env = traverse;
		} else {

			trail->next = traverse;
		}
	}

	error = PAM_SUCCESS;
out:
	if (error != PAM_SUCCESS) {
		if (traverse) {
			if (traverse->name)
				free(traverse->name);
			if (traverse->value)
				free(traverse->value);
			free(traverse);
		}
	}
	if (name)
		free(name);
	if (value)
		free(value);
	return (error);
}
