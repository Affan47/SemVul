CLASS_add_extern(CLASS *class, TRANS_EXTERN *decl)
{
	EXTFUNC *extfunc;
	int i;
	CLASS_SYMBOL *sym;
	int count;

	count = ARRAY_count(class->ext_func);
	if (count >= MAX_CLASS_EXTERN)
		THROW("Too many external functions");

	extfunc = ARRAY_add_void(&class->ext_func);
	TYPE_clear(&extfunc->type);
	extfunc->nparam = 0;
	extfunc->name = NO_SYMBOL;

	if (!decl) return;

	sym = CLASS_declare(class, decl->index, TRUE);


	sym->global.type = decl->type;
	sym->global.value = ARRAY_count(class->ext_func) - 1;

	extfunc->nparam = decl->nparam;

	if (extfunc->nparam)
	{
		ALLOC(&extfunc->param, decl->nparam * sizeof(PARAM), "CLASS_add_extern");

		for (i = 0; i < decl->nparam; i++)
		{
			extfunc->param[i].type = decl->param[i].type;
			extfunc->param[i].index = decl->param[i].index;
		}
	}

	extfunc->type = decl->type;
	extfunc->name = decl->index;
	extfunc->library = decl->library;
	extfunc->alias = decl->alias;
}
