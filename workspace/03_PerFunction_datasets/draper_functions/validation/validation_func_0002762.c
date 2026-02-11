restore_waterlevel(fd)
register int fd;
{
	register struct bubble *b = (struct bubble *)0, *btmp;
	register int i;
	int n;

	if (!Is_waterlevel(&u.uz)) return;

	set_wportal();
	mread(fd,(genericptr_t)&n,sizeof(int));
	mread(fd,(genericptr_t)&xmin,sizeof(int));
	mread(fd,(genericptr_t)&ymin,sizeof(int));
	mread(fd,(genericptr_t)&xmax,sizeof(int));
	mread(fd,(genericptr_t)&ymax,sizeof(int));
	for (i = 0; i < n; i++) {
		btmp = b;
		b = (struct bubble *)alloc(sizeof(struct bubble));
		mread(fd,(genericptr_t)b,sizeof(struct bubble));
		if (bbubbles) {
			btmp->next = b;
			b->prev = btmp;
		} else {
			bbubbles = b;
			b->prev = (struct bubble *)0;
		}
		mv_bubble(b,0,0,TRUE);
	}
	ebubbles = b;
	b->next = (struct bubble *)0;
	was_waterlevel = TRUE;
}
