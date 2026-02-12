static void remove_duplicate_parents(struct commit *commit)
{
	struct commit_list **pp, *p;


	pp = &commit->parents;
	while ((p = *pp) != NULL) {
		struct commit *parent = p->item;
		if (parent->object.flags & TMP_MARK) {
			*pp = p->next;
			continue;
		}
		parent->object.flags |= TMP_MARK;
		pp = &p->next;
	}

	for (p = commit->parents; p; p = p->next)
		p->item->object.flags &= ~TMP_MARK;
}
