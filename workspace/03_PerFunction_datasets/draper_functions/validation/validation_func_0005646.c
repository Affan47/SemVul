x_t_hot(KILL_NODE *node, ARTICLE *articles, SUBJECT *subj)
{
    long	n = 0;
    ARTICLE	*art, *thr;

    while (subj) {
	thr = art = subj->thread;
	if (THREAD_HAS_UNREAD(subj))
	    while (art)
		if (art->xref &&
		    regexec(node->expr_re, art->xref, 0, NULL, 0) == 0) {
		    n += mark_subthread_hot(art, node->pixmap);
		    art = preorder_skip_subthread(art);
		} else
		    art = next_in_thread_preorder(art);
	do {
	    subj = subj->next;
	} while (subj && subj->thread == thr);
    }

    return n;
}
