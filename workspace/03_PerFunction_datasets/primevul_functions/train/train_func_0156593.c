static void add_one_entry (struct commonio_db *db,
                           struct commonio_entry *p)
{

	p->next = NULL;
	p->prev = db->tail;

	if (NULL == db->head) {
		db->head = p;
	}
	if (NULL != db->tail) {
		db->tail->next = p;
	}
	db->tail = p;
}
