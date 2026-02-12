static int hash__init_new_context(struct mm_struct *mm)
{
	int index;


	if (mm->context.id == 0)
		slice_init_new_context_exec(mm);

	index = realloc_context_ids(&mm->context);
	if (index < 0)
		return index;

	subpage_prot_init_new_context(mm);

	pkey_mm_init(mm);
	return index;
}
