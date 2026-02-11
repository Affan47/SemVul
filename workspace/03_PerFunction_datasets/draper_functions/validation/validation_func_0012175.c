print_unload_info(struct seq_file *m, struct module *mod)
{
	struct module_use *use;
	int printed_something = 0;

	seq_printf(m, " %i ", module_refcount(mod));


	list_for_each_entry(use, &mod->source_list, source_list) {
		printed_something = 1;
		seq_printf(m, "%s,", use->source->name);
	}

	if (mod->init != NULL && mod->exit == NULL) {
		printed_something = 1;
		seq_puts(m, "[permanent],");
	}

	if (!printed_something)
		seq_puts(m, "-");
}
