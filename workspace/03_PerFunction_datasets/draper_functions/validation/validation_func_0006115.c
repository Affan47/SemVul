gretl_VAR_set_name (GRETL_VAR *var, const char *name)
{
    if (name == var->name) {
	return;
    }

    if (var->name == NULL) {
	var->name = malloc(MAXSAVENAME);
    }

    if (var->name != NULL) {
	*var->name = '\0';
	strncat(var->name, name, MAXSAVENAME - 1);
    }
}
