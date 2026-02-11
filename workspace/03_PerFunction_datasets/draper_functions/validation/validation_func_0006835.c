get_spell_index(const struct object *object, int index)
{
	struct spell *sp;

	for (sp = object->kind->spells; sp; sp = sp->next)
		if (sp->snum == index)
			return sp->spell_index;
	return -1;
}
