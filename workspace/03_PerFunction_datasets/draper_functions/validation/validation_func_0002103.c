print_boolorauto(cfg_printer_t *pctx, const cfg_obj_t *obj) {
	if (obj->type->rep == &cfg_rep_void)
		cfg_print_chars(pctx, "auto", 4);
	else if (obj->value.boolean)
		cfg_print_chars(pctx, "yes", 3);
	else
		cfg_print_chars(pctx, "no", 2);
}
