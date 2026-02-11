compare_accelerator(accelerator_t *accelerator1, accelerator_t *accelerator2) {
	int different = 0;
	event_t *ev1 = NULL, *ev2 = NULL;
	if(!different &&
	   ((accelerator1->memopt != accelerator2->memopt) ||
	   (accelerator1->lvc.version != accelerator2->lvc.version) ||
	   (accelerator1->lvc.characts != accelerator2->lvc.characts)))
		different = 1;
	ev1 = accelerator1->events;
	ev2 = accelerator2->events;
	while(!different && ev1 && ev2) {
		if(!different &&
		   ((ev1->id != ev2->id) ||
		   (ev1->flags != ev2->flags)))
			different = 1;
		ev1 = ev1->next;
		ev2 = ev2->next;
	}
	if(!different &&
	   ((ev1 && !ev2) || (!ev1 && ev2)))
		different = 1;
	return different;
}
