libmail_kwmCmp(struct libmail_kwMessage *km1,
	       struct libmail_kwMessage *km2)
{
	struct libmail_kwMessageEntry *e1, *e2;

	for (e1=km1->firstEntry, e2=km2->firstEntry; e1 && e2;
	     e1=e1->next, e2=e2->next)
		if (strcmp(keywordName(e1->libmail_keywordEntryPtr),
			   keywordName(e2->libmail_keywordEntryPtr)))
			break;

	return e1 || e2 ? -1:0;
}
