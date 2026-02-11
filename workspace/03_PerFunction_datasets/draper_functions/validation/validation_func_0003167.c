capability_orphan(struct CapabilityIndex *idx, const char *cap)
{
	struct CapabilityEntry *entry;

	s_assert(idx != NULL);

	entry = irc_dictionary_retrieve(idx->cap_dict, cap);
	if (entry != NULL)
	{
		entry->flags &= ~CAP_REQUIRED;
		entry->flags |= CAP_ORPHANED;
	}
}
