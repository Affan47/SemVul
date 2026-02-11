ndmp_enum_from_str (int *valp, char *str, struct ndmp_enum_str_table *table)
{
	for (; table->name; table++) {
		if (strcmp(table->name, str) == 0) {
			*valp = table->value;
			return 1;
		}
	}

	return 0;
}
