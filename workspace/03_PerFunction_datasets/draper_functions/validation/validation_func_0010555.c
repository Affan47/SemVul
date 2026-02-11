getNextFocus()
{
	CursesContainer *p=getParent();
	Curses *child=this;

	while (p != NULL)
	{
		size_t i;
		Curses *nextFocusPtr=NULL;

		for (i=0; i<p->children.size(); i++)
			if ( childPositionCompareFunc(child,
						      p->children[i].child) &&
			     (nextFocusPtr == NULL ||
			      childPositionCompareFunc(p->children[i].child,
						       nextFocusPtr)))
				nextFocusPtr=p->children[i].child;

		if (nextFocusPtr)
			return nextFocusPtr;

		if (p->isDialog())
			break;

		child=p;
		p=p->getParent();
	}
	return NULL;
}
