update(int fake, Node *node)
{
	Arc *a;

	MADESET(node, fake? BEINGMADE : MADE);
	if(((node->flags&VIRTUAL) == 0) && (access(node->name, 0) == 0)){
		node->time = timeof(node->name, 1);
		node->flags &= ~(CANPRETEND|PRETENDING);
		for(a = node->prereqs; a; a = a->next)
			if(a->prog)
				outofdate(node, a, 1);
	} else {
		node->time = 1;
		for(a = node->prereqs; a; a = a->next)
			if(a->n && outofdate(node, a, 1))
				node->time = a->n->time;
	}

}
