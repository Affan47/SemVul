get_rev(void)
{
	struct commit *commit = NULL;

	while (commit == NULL) {
		unsigned int mark;
		struct commit_list* parents;

		if (rev_list == NULL || non_common_revs == 0)
			return NULL;

		commit = rev_list->item;
		if (!(commit->object.parsed))
			parse_commit(commit);
		commit->object.flags |= POPPED;
		if (!(commit->object.flags & COMMON))
			non_common_revs--;

		parents = commit->parents;

		if (commit->object.flags & COMMON) {

			commit = NULL;
			mark = COMMON | SEEN;
		} else if (commit->object.flags & COMMON_REF)

			mark = COMMON | SEEN;
		else

			mark = SEEN;

		while (parents) {
			if (!(parents->item->object.flags & SEEN))
				rev_list_push(parents->item, mark);
			if (mark & COMMON)
				mark_common(parents->item, 1, 0);
			parents = parents->next;
		}

		rev_list = rev_list->next;
	}

	return commit->object.sha1;
}
