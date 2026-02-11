symtab_resolver_resolve(
	const struct symbol_table *symtab,
	struct data_definition *data
)
{
	struct symbol_table_container_ref *i;

	if (data->resolver.name == NULL) {
		return;
	}

	for (i = symtab->container_head; i != NULL; i = i->next) {
		if (strcmp(i->name, data->resolver.name) == 0) {
			data->resolver.container = i->container;
			symtab->callbacks->free(data->resolver.name);
			return;
		}
	}

	symtab->callbacks->log(FAUHDLI_LOG_ERROR, "fauhdli", "symbol_table",
		"could not resolver resolution function %s\n",
		data->resolver.name);
}
