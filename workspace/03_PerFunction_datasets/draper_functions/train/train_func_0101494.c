next_in_thread_wrap(ARTICLE *art)
{
    int height = 0;
    int flag = FALSE;

    do {
	while (!A_SIBLING(art) && A_PARENT(art)) {
	    art = A_PARENT(art);
	    height++;
	}

	if (A_SIBLING(art))
	    art = A_SIBLING(art);
	else {
	    if (flag)
		return NULL;
	    art = art->subject->thread;
	    flag = True;
	    height++;
	}

	while (height > 0 && A_CHILD1(art)) {
	    art = A_CHILD1(art);
	    height--;
	}
    } while (height > 0);

    return art;
}
