dictionary_set(dictionary *d, char *key, char *val)
{
	int i;
	unsigned hash;

	if (d==NULL || key==NULL)
		return -1;


	hash = dictionary_hash(key);

	if (d->n > 0) {
		for (i = 0; i < d->size; i++) {
			if (d->key[i] == NULL)
				continue;

			if (hash == d->hash[i]) {

				if (!strcmp(key, d->key[i])) {

					if (d->val[i] != NULL)
						free(d->val[i]);
					d->val[i] = val ? strdup(val) : NULL;

					return 0;
				}
			}
		}
	}


	if (d->n == d->size) {

		d->val  = (char **) mem_double(d->val, d->size * sizeof(char *));
		d->key  = (char **) mem_double(d->key, d->size * sizeof(char *));
		d->hash = (unsigned int *)
			mem_double(d->hash, d->size * sizeof(unsigned));
		if ((d->val == NULL) || (d->key == NULL) || (d->hash == NULL))

			return -1;

		d->size *= 2;
	}


	for (i = 0; i < d->size; i++) {
		if (d->key[i] == NULL) {

			break;
		}
	}

	d->key[i] = strdup(key);
	d->val[i] = val ? strdup(val) : NULL;
	d->hash[i] = hash;
	d->n ++;
	return 0;
}
