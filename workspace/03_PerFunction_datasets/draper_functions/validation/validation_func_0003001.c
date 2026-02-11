desc_unique_string(vector_t *v, const char *str)
{
	unsigned int i;
	desc_t *desc;

	for (i = 0; i < vector_active(v); i++) {
		if ((desc = vector_slot(v, i)) != NULL) {
			if (strcmp(desc->cmd, str) == 0) {
				return 1;
			}
		}
	}

	return 0;
}
