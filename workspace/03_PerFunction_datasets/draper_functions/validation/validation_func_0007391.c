removefilter(struct filter *f)
{
    if (f->action->removefilter != NULL)
	f->action->removefilter(f);
    if (f->previous != NULL)
	f->previous->next = f->next;
    else
	f->queue->first = f->next;
    if (f->next != NULL)
	f->next->previous = f->previous;
    else
	f->queue->last = f->previous;
    f->queue->isinitialized = 0;
}
