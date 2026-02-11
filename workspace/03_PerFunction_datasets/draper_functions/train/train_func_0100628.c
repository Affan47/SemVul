gdCacheDelete(gdCache_head_t *head)
{
	gdCache_element_t *elem, *prev;

	elem = head->mru;
	while(elem) {
		(*(head->gdCacheRelease))(elem->userdata);
		prev = elem;
		elem = elem->next;
		gdFree((char *)prev);
	}

	gdFree((char *)head);
}
