config_write_plugins(FILE *f)
{
	plugin_t *p;

	if (!f)
		return;

	for (p = plugins; p; p = p->next) {
		if (p->name) fprintf(f, "plugin %s %d\n", p->name, p->prio);
	}
}
