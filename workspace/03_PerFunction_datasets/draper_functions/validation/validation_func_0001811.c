removenode (Node *p)
{
    if (!p) return;


    p->next->prev = p->prev;
    p->prev->next = p->next;


    if (p->hashnext)
    {
	p->hashnext->hashprev = p->hashprev;
	p->hashprev->hashnext = p->hashnext;
    }
}
