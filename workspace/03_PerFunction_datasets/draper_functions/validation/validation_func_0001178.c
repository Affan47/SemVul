pp_variant_map_set_strset(PP_VariantMap *m,
	const char *name,
	const char **strs,
	unsigned int count)
{
	Passenger::VariantMap *vm = (Passenger::VariantMap *) m;
	std::set<string> the_set;

	for (unsigned int i = 0; i < count; i++) {
		the_set.insert(strs[i]);
	}
	vm->setStrSet(name, the_set);
}
